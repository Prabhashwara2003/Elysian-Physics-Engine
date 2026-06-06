#pragma once


#include "vectors.h"
#include "Object.h"

class Transform
{
public:

	vec2 position;
	float rotation;
	vec2 scale;

	Transform(vec2 position, float rotation, vec2 scale);
	void Translate(vec2 newPosition);
	void Rotate(float angle);

};

