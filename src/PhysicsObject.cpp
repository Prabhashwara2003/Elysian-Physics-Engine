#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(float xPosition, float yPosition, bool gravityOn)
	: xPosition(xPosition), yPosition(yPosition), gravityOn(gravityOn)
{
	
}

void PhysicsObject::update(float deltaTime) {
	if (gravityOn)
	{
		velocity = gravity.applyGravity(yPosition, deltaTime, velocity);
		if (yPosition >= 825)
		{
			yPosition = 825;
			velocity = -velocity * .8f;
		}
		yPosition += velocity * deltaTime *100;
	}
}

