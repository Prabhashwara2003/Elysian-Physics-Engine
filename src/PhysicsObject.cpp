#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(vec2 position, bool gravityOn)
	: position(position), gravityOn(gravityOn)
{
	
}

void PhysicsObject::update(float deltaTime) {
	if (gravityOn)
	{
		velocity = gravity.applyGravity(position.y, deltaTime, velocity);

		position.y += velocity.y * deltaTime * 100;

		if (position.y >= 825)
		{
			position.y = 825;
			velocity.y = -velocity.y * .8f;
		}

		
	}

}

