#include "vectors.h"
#include <cmath>

namespace elysian {

bool operator== (const vec2& l, const vec2& r) noexcept {
	return CMP(l.x, r.x) && CMP(l.y, r.y);
}

bool operator!= (const vec2& l, const vec2& r) noexcept {
	return !(l == r);
}

vec2 Cross(float scalar, const vec2& v) noexcept {
	return vec2(-scalar * v.y, scalar * v.x);
}

float Magnitude(const vec2& v) noexcept {
	return std::sqrt(Dot(v, v));
}

float Distance(const vec2& l, const vec2& r) noexcept {
	vec2 t = l - r;
	return Magnitude(t);
}

void Normalize(vec2& v) noexcept {
	v = v * (1.0f / Magnitude(v));
}

vec2 Normalized(const vec2& v) noexcept {
	return v * (1.0f / Magnitude(v));
}

float Angle(const vec2& l, const vec2& r) noexcept {
	return RAD2DEG(std::acos(Dot(l, r) / (Magnitude(l) * Magnitude(r))));
}

vec2 Projection(const vec2& v, const vec2& direction) noexcept {
	float dot = Dot(v, direction);
	float magnitudesqr = Magnitudesqr(direction);
	return direction * (dot / magnitudesqr);
}

vec2 Perpendicular(const vec2& v, const vec2& direction) noexcept {
	return v - Projection(v, direction);
}

vec2 Reflection(const vec2& v, const vec2& direction) noexcept {
	return v - Projection(v, direction) * 2.0f;
}

} // namespace elysian
