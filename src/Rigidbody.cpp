#include "Rigidbody.h"

Rigidbody::Rigidbody(float deltaTime) {
	this->deltaTime = deltaTime;
}

void Rigidbody::ApplyGravity() {
	accumulatedForces = accumulatedForces + vec2(0, 6);
}

void Rigidbody::Integrate() {
	if (isGravityOn) {
		ApplyGravity;
	}

	acceleration = accumulatedForces * inverseMass;
	velocity = velocity + acceleration * deltaTime;
	velocity = velocity * (1.0f - drag.x * deltaTime);
	transform.Translate(velocity * deltaTime);

	angularVelocity = angularVelocity + (accumulatedTorque * inverseMass);
	angularDrag = angularDrag * (1.0f - angularDrag.x * deltaTime);
	transform.Rotate(angularVelocity * deltaTime);

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
	vec2 r = position - transform.position;
	accumulatedForces = accumulatedForces + force;
	accumulatedTorque = accumulatedTorque + Cross(r, force);	
}