#include "Rigidbody.h"

Rigidbody::Rigidbody(vec2 position, float rotation, vec2 scale) {
	mass = 1.0f;
	accumulatedForces = vec2(0, 0);
	accumulatedTorque = 0;
	impulses = vec2(0, 0);
	isGravityOn = true;
	acceleration = vec2(0, 0);
	velocity = vec2(0, 0);
	angularVelocity = 0;
	drag = vec2(0.1f, 0.1f);
	angularDrag = vec2(0.1f, 0.1f);
	transform = new Transform(position, rotation, scale);
}

void Rigidbody::ApplyGravity() {
	accumulatedForces = accumulatedForces + vec2(0, 6);
}

void Rigidbody::Integrate(float deltaTime) {
	if (isGravityOn) {
		ApplyGravity();
	}

	acceleration = accumulatedForces * inverseMass;
	velocity = velocity + acceleration * deltaTime;
	velocity = velocity * (1.0f - drag.x * deltaTime);
	transform->Translate(velocity * deltaTime);

	angularVelocity = angularVelocity + (accumulatedTorque * inverseMass);
	angularDrag = angularDrag * (1.0f - angularDrag.x * deltaTime);
	transform->Rotate(angularVelocity * deltaTime);

	accumulatedForces = vec2(0, 0);
	accumulatedTorque = 0;
}

void Rigidbody::ApplyForce(vec2 force) {
	accumulatedForces = accumulatedForces + force;
}

void Rigidbody::ApplyImpulse(vec2 impulse) {
	impulses = impulses + impulse;
}

void Rigidbody::ApplyTorque(float torque) {
	accumulatedTorque = accumulatedTorque + torque;
}

void Rigidbody::ApplyForceAtPosition(vec2 force, Point2D position) {
	vec2 r = position - transform->position;
	accumulatedForces = accumulatedForces + force;
	accumulatedTorque = accumulatedTorque + Cross(r, force);	
}