#pragma once
#ifndef _H_MATH_MATRICES_
#define _H_MATH_MATRICES_

#include "PhysicsEngine/Export.h"
#include "vectors.h"

namespace elysian {

struct mat2 {
	union {
		struct {
			float _11, _12,
				_21, _22;
		};
		float asArray[4];
	};
	constexpr float* operator[](int i) { return &(asArray[i * 2]); }
	constexpr const float* operator[](int i) const { return &(asArray[i * 2]); }
	constexpr mat2() noexcept : _11(1.0f), _12(0.0f), _21(0.0f), _22(1.0f) {}
	constexpr mat2(float f11, float f12, float f21, float f22) noexcept
		: _11(f11), _12(f12), _21(f21), _22(f22) {}
};

struct mat3 {
	union {
		struct {
			float _11, _12, _13,
				_21, _22, _23,
				_31, _32, _33;
		};
		float asArray[9];
	};
	constexpr float* operator[](int i) { return &(asArray[i * 3]); }
	constexpr const float* operator[](int i) const { return &(asArray[i * 3]); }
	constexpr mat3() noexcept
		: _11(1.0f), _12(0.0f), _13(0.0f)
		, _21(0.0f), _22(1.0f), _23(0.0f)
		, _31(0.0f), _32(0.0f), _33(1.0f) {}
	constexpr mat3(float f11, float f12, float f13,
	               float f21, float f22, float f23,
	               float f31, float f32, float f33) noexcept
		: _11(f11), _12(f12), _13(f13)
		, _21(f21), _22(f22), _23(f23)
		, _31(f31), _32(f32), _33(f33) {}
};

struct mat4 {
	union {
		struct {
			float _11, _12, _13, _14,
				_21, _22, _23, _24,
				_31, _32, _33, _34,
				_41, _42, _43, _44;
		};
		float asArray[16];
	};
	constexpr float* operator[](int i) { return &(asArray[i * 4]); }
	constexpr const float* operator[](int i) const { return &(asArray[i * 4]); }
	constexpr mat4() noexcept
		: _11(1.0f), _12(0.0f), _13(0.0f), _14(0.0f)
		, _21(0.0f), _22(1.0f), _23(0.0f), _24(0.0f)
		, _31(0.0f), _32(0.0f), _33(1.0f), _34(0.0f)
		, _41(0.0f), _42(0.0f), _43(0.0f), _44(1.0f) {}
};

PHYSICSENGINE_API void Transpose(const float* srcMat, float* dstMat, int srcRow, int srcCol);
PHYSICSENGINE_API mat2 Transpose(const mat2& matrix) noexcept;
PHYSICSENGINE_API mat3 Transpose(const mat3& matrix) noexcept;
PHYSICSENGINE_API mat4 Transpose(const mat4& matrix) noexcept;

PHYSICSENGINE_API mat2 operator* (const mat2& matrix, float scalar) noexcept;
PHYSICSENGINE_API mat3 operator* (const mat3& matrix, float scalar) noexcept;
PHYSICSENGINE_API bool Multiply(float* out, const float* matA, int aRow, int aCol, const float* matB, int bRow, int bCol) noexcept;
PHYSICSENGINE_API mat2 operator* (const mat2& matA, const mat2& matB) noexcept;
PHYSICSENGINE_API mat3 operator* (const mat3& matA, const mat3& matB) noexcept;

PHYSICSENGINE_API mat3 createTranslation(vec2 position) noexcept;
PHYSICSENGINE_API mat3 createRotation(float angle) noexcept;
PHYSICSENGINE_API mat3 createScale(vec2 scalev) noexcept;

} // namespace elysian

#endif // _H_MATH_MATRICES_
