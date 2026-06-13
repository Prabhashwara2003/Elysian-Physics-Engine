#pragma once
#ifndef _H_2D_GEOMETRY_
#define _H_2D_GEOMETRY_

#include "PhysicsEngine/Export.h"
#include "vectors.h"

namespace elysian {

#ifndef CLAMP
#define CLAMP(number, minimum, maximum) \
	do { \
		if ((number) < (minimum)) (number) = (minimum); \
		else if ((number) > (maximum)) (number) = (maximum); \
	} while(0)
#endif

typedef vec2 Point2D;

struct Line2D {
	Point2D Start;
	Point2D End;

	inline constexpr Line2D() noexcept {}
	inline constexpr Line2D(const Point2D& start, const Point2D& end) noexcept
		: Start(start), End(end) {}
};

struct Circle {
	Point2D Position;
	float radius;

	inline constexpr Circle() noexcept : radius(1.0f) {}
	inline constexpr Circle(const Point2D& Position, float radius) noexcept
		: Position(Position), radius(radius) {}
};

struct Rectangle2D {
	Point2D origin;
	vec2 size;

	inline constexpr Rectangle2D() noexcept : size(1.0f, 1.0f) {}
	inline constexpr Rectangle2D(const Point2D& position, const vec2& size) noexcept
		: origin(position), size(size) {}
};

struct OrientedRectangle {
	Point2D position;
	vec2 halfExtents;
	float rotation;

	inline constexpr OrientedRectangle() noexcept
		: position(0, 0), halfExtents(1.0f, 1.0f), rotation(0) {}
	inline constexpr OrientedRectangle(const Point2D& position, const vec2& halfExtents) noexcept
		: position(position), halfExtents(halfExtents), rotation(0) {}
	inline constexpr OrientedRectangle(const Point2D& position, const vec2& halfExtents, float rotation) noexcept
		: position(position), halfExtents(halfExtents), rotation(rotation) {}
};

struct Interval2D {
	float min;
	float max;
};

PHYSICSENGINE_API float Length(const Line2D& Line) noexcept;
PHYSICSENGINE_API float LengthSqr(const Line2D& Line) noexcept;

PHYSICSENGINE_API vec2 GetMin(const Rectangle2D& rectangle) noexcept;
PHYSICSENGINE_API vec2 GetMax(const Rectangle2D& rectangle) noexcept;
PHYSICSENGINE_API Rectangle2D FromMinMax(const vec2& min, const vec2& max) noexcept;

PHYSICSENGINE_API bool PointInLine(const Point2D& Point, const Line2D& line) noexcept;
PHYSICSENGINE_API bool PointInCircle(const Point2D& Point, const Circle& circle) noexcept;
PHYSICSENGINE_API bool PointInRectangle(const Point2D& point, const Rectangle2D& rectangle) noexcept;
PHYSICSENGINE_API bool PointInOrientedRectangle(const Point2D& point, const OrientedRectangle& rectangle) noexcept;

PHYSICSENGINE_API bool LineCircle(const Line2D& line, const Circle& circle) noexcept;
PHYSICSENGINE_API bool LineRectangle(const Line2D& line, const Rectangle2D& rectangle) noexcept;
PHYSICSENGINE_API bool LineOrientedRectangle(const Line2D& line, const OrientedRectangle& rectangle) noexcept;

PHYSICSENGINE_API bool CircleCircle(const Circle& c1, const Circle& c2) noexcept;
PHYSICSENGINE_API bool CircleRectangle(const Circle& circle, const Rectangle2D& rectangle) noexcept;
PHYSICSENGINE_API bool CircleOrientedRectangle(const Circle& circle, const OrientedRectangle& rectangle) noexcept;

PHYSICSENGINE_API Interval2D GetInterval(const Rectangle2D& rect, const vec2& axis) noexcept;
PHYSICSENGINE_API bool OverlapOnAxis(const Rectangle2D& rect1, const Rectangle2D& rect2, const vec2 axis) noexcept;
PHYSICSENGINE_API bool RectangleRectangleSAT(const Rectangle2D& rect1, const Rectangle2D& rect2) noexcept;

PHYSICSENGINE_API Interval2D GetInterval(const OrientedRectangle& rectangle, const vec2& axis) noexcept;
PHYSICSENGINE_API bool OverlapOnAxis(const Rectangle2D& rect1, const OrientedRectangle& rect2, const vec2& axis) noexcept;
PHYSICSENGINE_API bool RectangleOrientedRectangle(const Rectangle2D& rect1, const OrientedRectangle rect2) noexcept;

PHYSICSENGINE_API bool OverlapOnAxis(const OrientedRectangle& rect1, const OrientedRectangle& rect2, const vec2& axis) noexcept;
PHYSICSENGINE_API bool RectangleOrientedRectangle(const OrientedRectangle& rect1, const OrientedRectangle& rect2) noexcept;

} // namespace elysian

#endif // _H_2D_GEOMETRY_
