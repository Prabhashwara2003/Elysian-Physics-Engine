#pragma once
#ifndef _H_RIGIDBODY
#define _H_RIGIDBODY

#include "PhysicsSystem.h"
#include "Geometry2D.h"
#include <vector>
#include "Transform.h"

class Rigidbody : Object
{
public:

	float deltaTime;
	float mass;
	vec2 accumulatedForces;
	float accumulatedTorque;
	vec2 impulses;
	bool isGravityOn;
	vec2 acceleration;
	vec2 velocity;
	float angularVelocity;
	vec2 drag;
	vec2 angularDrag;
	//Transform transform;

	float inverseMass = 1.0f / mass;
	

	Rigidbody(float deltaTime);
	virtual ~Rigidbody();

	void Integrate();
	virtual void Update(float deltaTime);
	virtual void ApplyForce(vec2 force);
	virtual void ApplyImpulse(vec2 impulse);
	virtual void ApplyForceAtPosition(vec2 force,Point2D position);
	virtual void ApplyTorque(float torque);
	void ApplyGravity();
};


#endif // !_H_RIGIDBODY


