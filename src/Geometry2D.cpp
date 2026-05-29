#include "Geometry2D.h"
#include <cmath>
#include <cfloat>
#include "matrices.h"


#define CMP(x,y)							\
	(fabsf((x) - (y)) <= FLT_EPSILON *		\
	fmaxf(1.0f,								\
	fmaxf(fabsf(x),fabsf(y))))		

#define RAG2DEG(x) ((x) * 57.295754f)
#define DEG2RAD(x) ((x) * 0.017453292f)

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

	return { fmaxf(p1.x,p2.x),fmaxf(p1.y,p2.y) };
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
		pointInRectangle(line.Start, rectangle)) {
		return true;
	}
	vec2 norm = Normalized(line.End - line.Start);
	norm.x = (norm.x != 0) ? 1.0f / norm.x : 0;
	norm.y = (norm.y != 0) ? 1.0f / norm.x : 0;
	vec2 min = (GetMin(rectangle) - line.Start) * norm;
	vec2 max = (GetMax(rectangle) - line.Start) * norm;
	float tmin = fmaxf(
		fminf(min.x, max.y),
		fminf(min.y, max.y)
	);
	float tmax = fminf(
		fminf(min.x, max.y),
		fminf(min.y, max.y)
	);
	if (tmax < 0 || tmin > tmax) {
		return false;
	}
	float t = (tmin < 0.0f) ? tmax : tmin;
	return t > 0.0f && t * t < LengthSqr(line);
}

bool LineOrintedRectangle(const Line2D& line, const OrientedRectangle& rectangle) {
	float theta = -DEG2RAD(rectangle.rotation);
	float zrotation2X2[] = { cosf(theta), sinf(theta), -sinf(theta) ,cosf(theta) };

	Line2D localLine;

	vec2 rotVector = line.Start - rectangle.position;
	Multiply(rotVector.asArray, vec2(rotVector.x, rotVector.y).asArray, 1, 2, zrotation2X2, 2, 2);

	localLine.End = rotVector + rectangle.halfExtents;

	Rectangle2D localRectangle(Point2D(), rectangle.halfExtents * 2.0f);
	return LineRectangle(localLine, localRectangle);
}

bool CircleCircle(const Circle& c1, const Circle& c2) {
	Line2D line (c1.Position, c2.Position);
	float radiusum = c1.radius + c2.radius;

	return LengthSqr(line) < radiusum * radiusum;
}
