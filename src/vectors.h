#pragma once
#ifndef _H_MATH_VECTORS_
#define _H_MATH_VECTORS_

//Structure definition
typedef struct vec2 {
	union {
		struct {
			float x;
			float y;
		};
		float asArray[2];
	};
	float& operator[] (int i) {
		return asArray[i];
	}
	
};

//for future implements
typedef struct vec3 {
	union {
		struct {
			float x;
			float y;
			float z;
		};
		float asArray[3];
	};
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
float Magnitude (const vec2& v);
float Magnitudesqr(const vec2& v);
float Distance(const vec2& l, const vec2& r);
void Normalize( vec2& v);
vec2 Normalized(const vec2& v);
float Angle(const vec2& l, const vec2& r);
vec2 Projection(const vec2& v, const vec2& direction);
vec2 Perpendicular(const vec2& v, const vec2& direction);
vec2 Reflection(const vec2& v, const vec2& direction);



#endif // !_H_MATH_VECTORS_
