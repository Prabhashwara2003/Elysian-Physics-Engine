#pragma once
#ifndef _H_RIGIDBODY
#define _H_RIGIDBODY

#include "Geometry2D.h"
#include "Transform.h"

namespace elysian {

class Rigidbody
{
public:
	
	float mass;
	float inverseMass;
	vec2 accumulatedForces;
	float accumulatedTorque;
	vec2 impulses;
	bool isGravityOn;
	vec2 acceleration;
	vec2 velocity;
	float angularVelocity;
	float drag;
	float angularDrag;
	Transform* transform;
	float bounciness;
	float friction;
	float gravityScale;

	Rigidbody(vec2 position, float rotation, vec2 scale);
	virtual ~Rigidbody();

	void Integrate(float deltaTime);
	void ApplyForce(vec2 force);
	void ApplyImpulse(vec2 impulse);
	void ApplyImpulseAtPosition(vec2 impulse, Point2D position, float momentOfInertia);
	void ApplyForceAtPosition(vec2 force, Point2D position);
	void ApplyTorque(float torque);
	void ApplyGravity(const vec2& gravity);
};

} // namespace elysian


#endif // !_H_RIGIDBODY


