#include "matrices.h"
#include <cmath>
#include <cfloat>

namespace elysian {

void Transpose(const float* srcMat, float* dstMat, int srcRow, int srcCol) {
	for (int i = 0;i < srcRow * srcCol; i++) {
		int row = i / srcRow;
		int col = i % srcRow;
		dstMat[i] = srcMat[srcCol * col + row];
	}
};

mat2 Transpose(const mat2& mat) {
	mat2 temp;
	Transpose(mat.asArray,temp.asArray, 2, 2);
	return temp;
}

mat3 Transpose(const mat3& mat) {
	mat3 temp;
	Transpose(mat.asArray, temp.asArray, 3, 3);
	return temp;
}

mat4 Transpose(const mat4& mat) {
	mat4 temp;
	Transpose(mat.asArray, temp.asArray, 4, 4);
	return temp;
}

mat2 operator* (const mat2& matrix, float scalar) {
	mat2 temp;
	for (int i = 0;i < 4;i++) {
		temp.asArray[i] = matrix.asArray[i];
	}
	return temp;
}

mat3 operator* (const mat3& matrix, float scalar) {
	mat3 temp;
	for (int i = 0; i < 9; i++) {
		temp.asArray[i] = matrix.asArray[i];
	}
	return temp;
}

bool Multiply(float* out, const float* matA, int aRow, int aCol, const float* matB, int bRow, int bCol) {
	if (aCol != bRow) {
		return false;
	}
	for (int i = 0; i < aRow; ++i) {
		for (int j = 0; j < bCol; ++j) {
			out[bCol * i + j] = 0.0f;
			for (int k = 0; k < bRow; ++k) {
				int a = aCol * i + k;
				int b = bCol * k + j;
				out[bCol * i + j] += matA[a] * matB[b];
			}
		}
	}
	return true;
}

mat2 operator* (const mat2& matA, const mat2& matB) {
	mat2 temp;
	Multiply(temp.asArray, matA.asArray, 2, 2, matB.asArray, 2, 2);
	return temp;
}

mat3 operator* (const mat3& matA, const mat3& matB) {
	mat3 temp;
	Multiply(temp.asArray, matA.asArray, 3, 3, matB.asArray, 3, 3);
	return temp;
}

mat3 createTranslation(vec2 position) {
	mat3 translation(1,0,position.x,0,1,position.y,0,0,1);
	return translation;
}

mat3 createRotation(float angle) {
	mat3 rotation(cos(angle), -sin(angle), 0, sin(angle), cos(angle), 0, 0, 0, 1);
	return rotation;
}

mat3 createScale(vec2 scalev) {
	mat3 scale(scalev.x, 0, 0, 0, scalev.y, 0, 0, 0, 1);
	return scale;
}

} // namespace elysian

