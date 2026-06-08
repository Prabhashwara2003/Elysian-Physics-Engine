#include "vectors.h"
#include <cmath>
#include <cfloat>	

vec2 operator+ (const vec2& l, const vec2& r) {
	return { l.x + r.x, l.y + r.y };
};

vec2 operator- (const vec2& l, const vec2& r) {
	return { l.x - r.x , l.y - r.y };
};

vec2 operator* (const vec2& l, const vec2& r) {
	return { l.x * r.x , l.y * r.y };
};

vec2 operator* (const vec2& l, const float& r) {
	return { l.x * r ,l.y * r };
};

bool operator== (const vec2& l, const vec2& r) {
	return CMP(l.x, r.x) && CMP(l.y, r.y);
};

bool operator!= (const vec2& l, const vec2& r) {
	return !(l == r);
};

float Dot(const vec2& l, const vec2& r) {
	return  l.x * r.x + l.y * r.y;
};

float Cross(const vec2& l, const vec2& r) {
	return l.x * r.y - l.y * r.x;
};

vec2 Cross(float scalar, const vec2& v) {
	return vec2(-scalar * v.y, scalar * v.x);
}

float Magnitude(const vec2& v){
	return sqrt(Dot(v, v));
};

float Magnitudesqr(const vec2& v) {
	return Dot(v, v);
};

float Distance(const vec2& l, const vec2& r) {
	vec2 t = l - r;
	return Magnitude(t);
}

void Normalize(vec2& v) {
	v =  v * (1.0f / Magnitude(v));
};

vec2 Normalized(const vec2& v) {
	return v * (1.0f / Magnitude(v));
};

float Angle(const vec2& l, const vec2& r) {
	return RAG2DEG(acosf(Dot(l, r) / (Magnitude(l) * Magnitude(r))));
};

vec2 Projection(const vec2& v, const vec2& direction) {
	float dot = Dot(v, direction);
	float magnitudesqr = Magnitudesqr(direction);
	return direction * (dot / magnitudesqr);
};

vec2 Perpendicular(const vec2& v, const vec2& direction) {
	return v - Projection(v, direction);
};

vec2 Reflection(const vec2& v, const vec2& direction) {
	return v - Projection(v, direction) * 2.0f;
};


