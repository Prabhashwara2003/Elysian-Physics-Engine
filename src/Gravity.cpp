#include "Gravity.h"

float Gravity::applyGravity(float y, float deltaTime, float velocity)
{
	velocity += downacceleration * deltaTime;
	y += velocity * deltaTime * 100;

	return velocity;
}