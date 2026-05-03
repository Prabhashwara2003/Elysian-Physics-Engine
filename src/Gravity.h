#pragma once

class Gravity
{
public:
	//float v = 0; // Initial velocity (m/s)
	float downacceleration = 9.8f; // Acceleration due to gravity (m/s^2)
	float applyGravity(float y, float deltaTime, float velocity);
};
