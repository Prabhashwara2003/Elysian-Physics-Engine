#pragma once
#ifndef _H_MATH_VECTORS_
#define _H_MATH_VECTORS_

#define CMP(x,y)							\
	(fabsf((x) - (y)) <= FLT_EPSILON *		\
	fmaxf(1.0f,								\
	fmaxf(fabsf(x),fabsf(y))))		

#define RAG2DEG(x) ((x) * 57.295754f)
#define DEG2RAD(x) ((x) * 0.017453292f)

namespace elysian {

//Structure definition
struct vec2 {
	union {
		struct {
			float x;
			float y;
		};
		float asArray[2];
	};

	vec2() : x(0), y(0) {}
	vec2(float x, float y) : x(x), y(y) {}

	float& operator[] (int i) {
		return asArray[i];
	}
	
};

//for future implements
struct vec3 {
	union {
		struct {
			float x;
			float y;
			float z;
		};
		float asArray[3];
	};

	vec3() : x(0), y(0), z(0) {}
	vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	float& operator[](int i) {
		return asArray[i];
	}
};

//Method declaration

vec2 operator+ (const vec2& l, const vec2& r);
vec2 operator- (const vec2& l, const vec2& r);
vec2 operator* (const vec2& l, const vec2& r);
vec2 operator* (const vec2& l, const float& r);
bool operator== (const vec2& l, const vec2& r);
bool operator!= (const vec2& l, const vec2& r);
float Dot (const vec2& l, const vec2& r);
float Cross(const vec2& l, const vec2& r);
vec2 Cross(float scalar, const vec2& v);
float Magnitude (const vec2& v);
float Magnitudesqr(const vec2& v);
float Distance(const vec2& l, const vec2& r);
void Normalize( vec2& v);
vec2 Normalized(const vec2& v);
float Angle(const vec2& l, const vec2& r);
vec2 Projection(const vec2& v, const vec2& direction);
vec2 Perpendicular(const vec2& v, const vec2& direction);
vec2 Reflection(const vec2& v, const vec2& direction);

} // namespace elysian

#endif // !_H_MATH_VECTORS_
