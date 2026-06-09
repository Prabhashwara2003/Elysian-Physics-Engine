#pragma once
#ifndef _H_2D_GEOMETRY_
#define _H_2D_GEOMETRY_

#include "vectors.h"

namespace elysian {

#ifndef CLAMP
#define CLAMP(number, minimum, maximum) number = (number < minimum) ? minimum : ((number > maximum) ? maximum : number)
#endif


typedef vec2 Point2D;

struct Line2D {
	Point2D Start;
	Point2D End;

	inline Line2D() {};
	inline Line2D(const Point2D& start, const Point2D& end)
		:Start(start), End(end)
	{

	}
};

struct Circle {
	Point2D Position;
	float radius;

	inline Circle() : radius(1.0) {};
	inline Circle(const Point2D& Position, const float& radius) 
		:Position(Position),radius(radius)
	{}
};

struct Rectangle2D {
	Point2D origin;
	vec2 size;

	inline Rectangle2D(): size(1.0f,1.0f){}
	inline Rectangle2D(const Point2D& position, const vec2& size)
		: origin(position), size(size)
	{};
};

struct OrientedRectangle {
	Point2D position;
	vec2 halfExtents;
	float rotation;

	inline OrientedRectangle() : position(0, 0), halfExtents(1.0f, 1.0f), rotation(0) {}
	inline OrientedRectangle(const Point2D& position ,const vec2& halfExtents)
		:position(position),halfExtents(halfExtents)
	{ }
	inline OrientedRectangle(const Point2D& position, const vec2& halfExtents ,const float& rotation)
		:position(position),halfExtents(halfExtents),rotation(rotation)
	{ }
};

struct Interval2D {
	float min;
	float max;
};

float Length(const Line2D& Line);
float LengthSqr(const Line2D& Line);

vec2 GetMin(const Rectangle2D& rectangle);
vec2 GetMax(const Rectangle2D& rectangle);
Rectangle2D FromMinMax(const vec2& min, const vec2& max);

bool PointInLine(const Point2D& Point, const Line2D& line);
bool PointInCircle(const Point2D& Point, const Circle& circle);
bool pointInRectangle(const Point2D& point, const Rectangle2D& rectangle);
bool pointInOrientedRectangle(const Point2D& point, const OrientedRectangle& rectangle);

bool LineCircle(const Line2D& line, const Circle& circle);
bool LineRectangle(const Line2D& line, const Rectangle2D& rectangle);
bool LineOrientedRectangle(const Line2D& line, const OrientedRectangle& rectangle);

bool CircleCircle(const Circle& c1, const Circle& c2);
bool CircleRectangle(const Circle& circle, const Rectangle2D& rectangle);
bool CircleOrientedRectangle(const Circle& circle, const OrientedRectangle& rectangle);

Interval2D GetInterval(const Rectangle2D& rect, const vec2& axis);
bool OverlapOnAxis(const Rectangle2D& rect1, const Rectangle2D& rect2, const vec2 axis);
bool RectangleRectangleSaT(const Rectangle2D& rect1, const Rectangle2D& rect2);

Interval2D GetInterval(const OrientedRectangle& rectangle, const vec2& axis);
bool OverlapOnAxis(const Rectangle2D& rect1, const OrientedRectangle& rect2, const vec2& axis);
bool RectangleOrientedRectangle(const Rectangle2D& rect1, const OrientedRectangle rect2);

bool OverlapOnAxis(const OrientedRectangle& rect1, const OrientedRectangle& rect2, const vec2& axis);
bool RectangleOrientedRectangle(const OrientedRectangle& rect1, const OrientedRectangle& rect2);

} // namespace elysian

#endif // _H_2D_GEOMETRY_

