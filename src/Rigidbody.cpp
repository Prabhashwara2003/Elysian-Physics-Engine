#include "Rigidbody.h"

namespace elysian {

Rigidbody::~Rigidbody() {}

Rigidbody::Rigidbody(vec2 position, float rotation, vec2 scale) {
	mass = 1.0f;
	accumulatedForces = vec2(0, 0);
	accumulatedTorque = 0;
	impulses = vec2(0, 0);
	isGravityOn = true;
	acceleration = vec2(0, 0);
	velocity = vec2(0, 0);
	angularVelocity = 0;
	drag = 0.1f;
	angularDrag = 0.1f;
	transform = new Transform(position, rotation, scale);
	bounciness = 0.5f;
	friction = 0.4f;
	gravityScale = 1.0f;
	inverseMass = 1.0f / mass;
}

void Rigidbody::Integrate(float deltaTime) {
	acceleration = accumulatedForces * inverseMass;
	velocity = velocity + acceleration * deltaTime;
	velocity = velocity * (1.0f - drag * deltaTime);
	transform->Translate(velocity * deltaTime);

	angularVelocity = angularVelocity + (accumulatedTorque * inverseMass);
	angularVelocity = angularVelocity * (1.0f - angularDrag * deltaTime);
	transform->Rotate(angularVelocity * deltaTime);

	accumulatedForces = vec2(0, 0);
	accumulatedTorque = 0;
}

void Rigidbody::ApplyGravity(const vec2& gravity) {
	accumulatedForces = accumulatedForces + gravity * gravityScale * mass;
}

void Rigidbody::ApplyForce(vec2 force) {
	accumulatedForces = accumulatedForces + force;
}

void Rigidbody::ApplyImpulse(vec2 impulse) {
	velocity = velocity + (impulse * inverseMass);
}

void Rigidbody::ApplyImpulseAtPosition(vec2 impulse, Point2D position, float momentOfInertia) {
	vec2 r = position - transform->position;
	angularVelocity += (r.x * impulse.y - r.y * impulse.x) / momentOfInertia;
	ApplyImpulse(impulse);
	
}

void Rigidbody::ApplyTorque(float torque) {
	accumulatedTorque = accumulatedTorque + torque;
}

void Rigidbody::ApplyForceAtPosition(vec2 force, Point2D position) {
	vec2 r = position - transform->position;
	accumulatedForces = accumulatedForces + force;
	accumulatedTorque = accumulatedTorque + Cross(r, force);	
}

} // namespace elysian