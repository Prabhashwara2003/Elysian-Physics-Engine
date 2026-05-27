#pragma once
#include "vectors.h"
#include "matrices.h"

class Circle
{
public:

	vec2 origin;
	float radius;
	float angle;
	mat3 Transform;
	mat3 Rotation;
	mat3 Translation;
	mat3 Scale;

	Circle(vec2 origin, float radius ,float angle);
	void update();
};

