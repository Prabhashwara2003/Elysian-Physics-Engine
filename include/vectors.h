#pragma once
#ifndef _H_MATH_VECTORS_
#define _H_MATH_VECTORS_

#include "PhysicsEngine/Export.h"
#include <cmath>
#include <cfloat>

#define CMP(x,y)							\
	(fabsf((x) - (y)) <= FLT_EPSILON *		\
	fmaxf(1.0f,								\
	fmaxf(fabsf(x),fabsf(y))))		

#define RAD2DEG(x) ((x) * 57.295754f)
#define DEG2RAD(x) ((x) * 0.017453292f)

namespace elysian {

struct vec2 {
	union {
		struct {
			float x;
			float y;
		};
		float asArray[2];
	};

	constexpr vec2() noexcept : x(0), y(0) {}
	constexpr vec2(float x, float y) noexcept : x(x), y(y) {}

	constexpr float& operator[] (int i) noexcept { return asArray[i]; }
	constexpr const float& operator[] (int i) const noexcept { return asArray[i]; }

	constexpr vec2& operator+=(const vec2& r) noexcept { x += r.x; y += r.y; return *this; }
	constexpr vec2& operator-=(const vec2& r) noexcept { x -= r.x; y -= r.y; return *this; }
	constexpr vec2& operator*=(const vec2& r) noexcept { x *= r.x; y *= r.y; return *this; }
	constexpr vec2& operator*=(float r) noexcept { x *= r; y *= r; return *this; }
	constexpr vec2 operator-() const noexcept { return vec2(-x, -y); }
};

struct vec3 {
	union {
		struct {
			float x;
			float y;
			float z;
		};
		float asArray[3];
	};

	constexpr vec3() noexcept : x(0), y(0), z(0) {}
	constexpr vec3(float x, float y, float z) noexcept : x(x), y(y), z(z) {}

	constexpr float& operator[](int i) noexcept { return asArray[i]; }
	constexpr const float& operator[](int i) const noexcept { return asArray[i]; }
};

constexpr vec2 operator+ (const vec2& l, const vec2& r) noexcept { return { l.x + r.x, l.y + r.y }; }
constexpr vec2 operator- (const vec2& l, const vec2& r) noexcept { return { l.x - r.x, l.y - r.y }; }
constexpr vec2 operator* (const vec2& l, const vec2& r) noexcept { return { l.x * r.x, l.y * r.y }; }
constexpr vec2 operator* (const vec2& l, float r) noexcept { return { l.x * r, l.y * r }; }
constexpr vec2 operator* (float l, const vec2& r) noexcept { return { l * r.x, l * r.y }; }
bool operator== (const vec2& l, const vec2& r) noexcept;
bool operator!= (const vec2& l, const vec2& r) noexcept;

constexpr float Dot(const vec2& l, const vec2& r) noexcept { return l.x * r.x + l.y * r.y; }
constexpr float Cross(const vec2& l, const vec2& r) noexcept { return l.x * r.y - l.y * r.x; }
PHYSICSENGINE_API vec2 Cross(float scalar, const vec2& v) noexcept;
PHYSICSENGINE_API float Magnitude(const vec2& v) noexcept;
constexpr float Magnitudesqr(const vec2& v) noexcept { return Dot(v, v); }
PHYSICSENGINE_API float Distance(const vec2& l, const vec2& r) noexcept;
PHYSICSENGINE_API void Normalize(vec2& v) noexcept;
PHYSICSENGINE_API vec2 Normalized(const vec2& v) noexcept;
PHYSICSENGINE_API float Angle(const vec2& l, const vec2& r) noexcept;
PHYSICSENGINE_API vec2 Projection(const vec2& v, const vec2& direction) noexcept;
PHYSICSENGINE_API vec2 Perpendicular(const vec2& v, const vec2& direction) noexcept;
PHYSICSENGINE_API vec2 Reflection(const vec2& v, const vec2& direction) noexcept;

} // namespace elysian

#endif // !_H_MATH_VECTORS_
