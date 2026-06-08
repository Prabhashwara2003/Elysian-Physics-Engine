#include "Geometry2D.h"
#include <cmath>
#include <cfloat>
#include "matrices.h"

namespace elysian {

float Length(const Line2D& Line) {
	return Magnitude(Line.Start - Line.End);
}
float LengthSqr(const Line2D& Line) {
	return Magnitudesqr(Line.Start - Line.End);
}

vec2 GetMin(const Rectangle2D& rectangle) {
	vec2 p1 = rectangle.origin;
	vec2 p2 = rectangle.origin + rectangle.size;
	return { fminf(p1.x, p2.x), fminf(p1.y, p2.y) };
}
vec2 GetMax(const Rectangle2D& rectangle) {
	vec2 p1 = rectangle.origin;
	vec2 p2 = rectangle.origin + rectangle.size;
	return { fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y) };
}
Rectangle2D FromMinMax(const vec2& min, const vec2& max) {
	return Rectangle2D(min, max - min);
}

bool PointInLine(const Point2D& Point, const Line2D& line) {
	float dy = line.Start.y - line.End.y;
	float dx = line.Start.x - line.End.x;
	float m = dy / dx;
	float c = line.Start.y - m * line.End.x;
	return CMP(Point.y, m * Point.x + c);
}
bool PointInCircle(const Point2D& Point, const Circle& circle) {
	Line2D line(Point, circle.Position);
	if (LengthSqr(line) < circle.radius * circle.radius) {
		return true;
	}
	return false;
}
bool pointInRectangle(const Point2D& point, const Rectangle2D& rectangle) {
	vec2 min = GetMin(rectangle);
	vec2 max = GetMax(rectangle);
	return min.x <= point.x &&
		min.y <= point.y &&
		point.x <= max.x &&
		point.y <= max.y;
}
bool pointInOrientedRectangle(const Point2D point, const OrientedRectangle& rectangle) {
	vec2 rotVector = point - rectangle.position;
	float theta = -DEG2RAD(rectangle.rotation);
	float zRotation2x2[] = { cosf(theta), sinf(theta), -sinf(theta) ,cosf(theta) };
	Multiply(rotVector.asArray, vec2(rotVector.x, rotVector.y).asArray, 1, 2, zRotation2x2, 2, 2);
	Rectangle2D localRectangle(Point2D(), rectangle.halfExtents * 2.0f);
	vec2 localPoint = rotVector + rectangle.halfExtents;
	return pointInRectangle(localPoint, localRectangle);
}

bool LineCircle(const Line2D& line, const Circle& circle) {
	vec2 ab = line.Start - line.End;
	float t = Dot(circle.Position - line.Start, ab) / Dot(ab, ab);
	if (t < 0.0f || t > 1.0f) {
		return false;
	}
	Point2D closestPoint = line.Start + ab * t;
	Line2D CircleToClosest(circle.Position, closestPoint);
	return LengthSqr(CircleToClosest) < circle.radius * circle.radius;
}
bool LineRectangle(const Line2D& line, const Rectangle2D& rectangle) {
	if (pointInRectangle(line.Start, rectangle) ||
		pointInRectangle(line.End, rectangle)) {
		return true;
	}
	vec2 norm = Normalized(line.End - line.Start);
	norm.x = (norm.x != 0) ? 1.0f / norm.x : 0;
	norm.y = (norm.y != 0) ? 1.0f / norm.y : 0;
	vec2 min = (GetMin(rectangle) - line.Start) * norm;
	vec2 max = (GetMax(rectangle) - line.Start) * norm;
	float tmin = fmaxf(
		fminf(min.x, max.x),
		fminf(min.y, max.y)
	);
	float tmax = fminf(
		fmaxf(min.x, max.x),
		fmaxf(min.y, max.y)
	);
	if (tmax < 0 || tmin > tmax) {
		return false;
	}
	float t = (tmin < 0.0f) ? tmax : tmin;
	return t > 0.0f && t * t < LengthSqr(line);
}
bool LineOrientedRectangle(const Line2D& line, const OrientedRectangle& rectangle) {
	float theta = -DEG2RAD(rectangle.rotation);
	float zrotation2X2[] = { cosf(theta), sinf(theta), -sinf(theta) ,cosf(theta) };
	Line2D localLine;
	vec2 rotVector = line.Start - rectangle.position;
	Multiply(rotVector.asArray, vec2(rotVector.x, rotVector.y).asArray, 1, 2, zrotation2X2, 2, 2);
	localLine.Start = rotVector + rectangle.halfExtents;
	rotVector = line.End - rectangle.position;
	Multiply(rotVector.asArray, vec2(rotVector.x, rotVector.y).asArray, 1, 2, zrotation2X2, 2, 2);
	localLine.End = rotVector + rectangle.halfExtents;
	Rectangle2D localRectangle(Point2D(), rectangle.halfExtents * 2.0f);
	return LineRectangle(localLine, localRectangle);
}

bool CircleCircle(const Circle& c1, const Circle& c2) {
	Line2D line(c1.Position, c2.Position);
	float radiusum = c1.radius + c2.radius;
	return LengthSqr(line) < radiusum * radiusum;
}
bool CircleRectangle(const Circle& circle, const Rectangle2D& rectangle) {
	vec2 min = GetMin(rectangle);
	vec2 max = GetMax(rectangle);
	vec2 closestPoint = circle.Position;
	CLAMP(closestPoint.x, min.x, max.x);
	CLAMP(closestPoint.y, min.y, max.y);
	Line2D line(closestPoint, circle.Position);
	return LengthSqr(line) <= circle.radius * circle.radius;
}
bool CircleOrientedRectangle(const Circle& circle, const OrientedRectangle& rectangle) {
	vec2 rotvector = circle.Position - rectangle.position;
	float theta = -DEG2RAD(rectangle.rotation);
	float zRotation2x2[] = { cosf(theta), sinf(theta), -sinf(theta), cosf(theta) };
	Multiply(rotvector.asArray, vec2(rotvector.x, rotvector.y).asArray, 1, 2, zRotation2x2, 2, 2);
	Circle lCircle(rotvector + rectangle.halfExtents, circle.radius);
	Rectangle2D lRect(Point2D(), rectangle.halfExtents * 2.0f);
	return CircleRectangle(lCircle, lRect);
}

Interval2D GetInterval(const Rectangle2D& rect, const vec2& axis) {
	Interval2D result;
	vec2 min = GetMin(rect);
	vec2 max = GetMax(rect);
	vec2 verts[] = { vec2(min.x, min.y), vec2(min.x, max.y), vec2(max.x, max.y), vec2(max.x, min.y) };
	result.min = result.max = Dot(axis, verts[0]);
	for (int i = 1; i < 4; i++) {
		float projection = Dot(axis, verts[i]);
		if (projection < result.min) {
			result.min = projection;
		}
		if (projection > result.max) {
			result.max = projection;
		}
	}
	return result;
}
bool OverlapOnAxis(const Rectangle2D& rect1, const Rectangle2D& rect2, const vec2 axis) {
	Interval2D a = GetInterval(rect1, axis);
	Interval2D b = GetInterval(rect2, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}
bool RectangleRectangleSaT(const Rectangle2D& rect1, const Rectangle2D& rect2) {
	vec2 axisToTest[] = { vec2(1, 0), vec2(0, 1) };
	for (int i = 0; i < 2; i++) {
		if (!OverlapOnAxis(rect1, rect2, axisToTest[i])) {
			return false;
		}
	}
	return true;
}

Interval2D GetInterval(const OrientedRectangle& rectangle, const vec2& axis) {
	Rectangle2D temp(Point2D(rectangle.position - rectangle.halfExtents), rectangle.halfExtents * 2.0f);
	Interval2D result;
	vec2 min = GetMin(temp);
	vec2 max = GetMax(temp);
	vec2 verts[] = { vec2(min.x, min.y), vec2(min.x, max.y), vec2(max.x, max.y), vec2(max.x, min.y) };
	float theta = DEG2RAD(rectangle.rotation);
	float zRotation[] = { cosf(theta), sinf(theta), -sinf(theta), cosf(theta) };
	for (int i = 0; i < 4; i++) {
		vec2 r = verts[i] - rectangle.position;
		vec2 rotated;
		Multiply(rotated.asArray, r.asArray, 1, 2, zRotation, 2, 2);
		verts[i] = rotated + rectangle.position;
	}
	result.min = result.max = Dot(axis, verts[0]);
	for (int i = 1; i < 4; i++) {
		float projection = Dot(axis, verts[i]);
		if (projection < result.min) {
			result.min = projection;
		}
		if (projection > result.max) {
			result.max = projection;
		}
	}
	return result;
}
bool OverlapOnAxis(const Rectangle2D& rect1, const OrientedRectangle& rect2, const vec2& axis) {
	Interval2D a = GetInterval(rect1, axis);
	Interval2D b = GetInterval(rect2, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}
bool RectangleOrientedRectangle(const Rectangle2D& rect1, const OrientedRectangle rect2) {
	vec2 axisToTest[] = { vec2(1, 0), vec2(0, 1), vec2(), vec2() };
	float theta = DEG2RAD(rect2.rotation);
	float zRotaion[] = { cosf(theta), sinf(theta), -sinf(theta), cosf(theta) };
	vec2 axis = Normalized(vec2(rect2.halfExtents.x, 0));
	Multiply(axisToTest[2].asArray, axis.asArray, 1, 2, zRotaion, 2, 2);
	axis = Normalized(vec2(0, rect2.halfExtents.y));
	Multiply(axisToTest[3].asArray, axis.asArray, 1, 2, zRotaion, 2, 2);
	for (int i = 0; i < 4; i++) {
		if (!OverlapOnAxis(rect1, rect2, axisToTest[i])) {
			return false;
		}
	}
	return true;
}

bool OverlapOnAxis(const OrientedRectangle& rect1, const OrientedRectangle& rect2, const vec2& axis) {
	Interval2D a = GetInterval(rect1, axis);
	Interval2D b = GetInterval(rect2, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}
bool RectangleOrientedRectangle(const OrientedRectangle& rect1, const OrientedRectangle& rect2) {
	vec2 axisToTest[] = { vec2(), vec2(), vec2(), vec2() };
	float theta1 = DEG2RAD(rect1.rotation);
	float theta2 = DEG2RAD(rect2.rotation);
	float zRotaion1[] = { cosf(theta1), sinf(theta1), -sinf(theta1), cosf(theta1) };
	float zRotaion2[] = { cosf(theta2), sinf(theta2), -sinf(theta2), cosf(theta2) };
	vec2 axis = Normalized(vec2(rect1.halfExtents.x, 0));
	Multiply(axisToTest[0].asArray, axis.asArray, 1, 2, zRotaion1, 2, 2);
	axis = Normalized(vec2(0, rect1.halfExtents.y));
	Multiply(axisToTest[1].asArray, axis.asArray, 1, 2, zRotaion1, 2, 2);
	axis = Normalized(vec2(rect2.halfExtents.x, 0));
	Multiply(axisToTest[2].asArray, axis.asArray, 1, 2, zRotaion2, 2, 2);
	axis = Normalized(vec2(0, rect2.halfExtents.y));
	Multiply(axisToTest[3].asArray, axis.asArray, 1, 2, zRotaion2, 2, 2);
	for (int i = 0; i < 4; i++) {
		if (!OverlapOnAxis(rect1, rect2, axisToTest[i])) {
			return false;
		}
	}
	return true;
}

} // namespace elysian
