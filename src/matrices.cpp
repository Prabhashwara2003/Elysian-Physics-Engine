#include "matrices.h"
#include <cmath>
#include <cfloat>

#define CMP(x,y)							\
	(fabsf((x) - (y)) <= FLT_EPSILON *		\
	fmaxf(1.0f,								\
	fmaxf(fabsf(x),fabsf(y))))		

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

