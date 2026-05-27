#pragma once
#ifndef _H_MATH_MATRICES_
#define _h_MATH_MATRICES_
#include "vectors.h"

//structure definition
typedef struct mat2 {
	union {
		struct {
			float _11, _12,
				_21, _22;
		};
		float asArray[4];
	};
	inline float* operator[](int i) {
		return &(asArray[i * 2]);
	}
	inline mat2(){
		_11 = _22 = 1.0f;
		_12 = _21 = 0.0f;
	}
	inline mat2(float f11 ,float f12 ,float f21 ,float f22) {
		_11 = f11;
		_12 = f12;
		_21 = f21;
		_22 = f22;
	}
};
typedef struct mat3 {
	union {
		struct {
			float _11, _12,_13,
				_21, _22,_23,
				_31,_32,_33;
		};
		float asArray[9];
	};
	inline float* operator[](int i) {
		return &(asArray[i * 3]);
	}
	inline mat3() {
		_11 = _22 = _33 = 1.0f;
		_12 = _13 = _21 = 0.0f;
		_23 = _31 = _32 = 0.0f;
	}
	inline mat3(float f11, float f12,float f13, float f21, float f22 ,float f23 ,float f31 ,float f32 ,float f33) {
		_11 = f11;
		_12 = f12;
		_13 = f13;
		_21 = f21;
		_22 = f22;
		_23 = f23;
		_31 = f31;
		_32 = f32;
		_33 = f33;
	}
};
typedef struct mat4 {
	union {
		struct {
			float _11, _12, _13,_14,
				_21, _22, _23,_24,
				_31, _32, _33,_34,
				_41,_42,_43,_44;
		};
		float asArray[16];
	};
	inline float* operator[](int i) {
		return &(asArray[i * 4]);
	}
};//for future implements

void Transpose(const float* srcMat, float* dstMat, int srcRow, int srcCol);
mat2 Transpose(const mat2& matrix);
mat3 Transpose(const mat3& matrix);
mat4 Transpose(const mat4& matrix);

mat2 operator* (const mat2& matrix, float scalar);
mat3 operator* (const mat3& matrix, float saclar);
bool Multiply(float* out, const float* matA, int aRow, int aCol, const float* matB, int bRow, int bCol);
mat2 operator* (const mat2& matA, const mat2& matB);
mat3 operator* (const mat3& matA, const mat3& matB);

#endif // _H_MATH_MATRICES_
