#include "Rigidbody.h"
#include <cmath>

namespace elysian {

	Rigidbody::Rigidbody(vec2 position, float rotation, vec2 scale) noexcept
		: transform(position, rotation, scale)
	{
		mass = 1.0f;
		inverseMass = 1.0f;
		momentOfInertia = 1.0f;
		inverseInertia = 1.0f;
		accumulatedForces = vec2(0, 0);
		accumulatedTorque = 0.0f;
		impulses = vec2(0, 0);
		isGravityOn = true;
		acceleration = vec2(0, 0);
		velocity = vec2(0, 0);
		angularVelocity = 0.0f;
		drag = 0.99f;
		angularDrag = 0.98f;
		bounciness = 0.5f;
		friction = 0.4f;
		gravityScale = 1.0f;
	}

	void Rigidbody::Integrate(float deltaTime) noexcept {
		acceleration = accumulatedForces * inverseMass;
		velocity = velocity + acceleration * deltaTime;

		transform.Translate(velocity * deltaTime);
		velocity = velocity * std::pow(drag, deltaTime * 60.0f);

		angularVelocity = angularVelocity + (accumulatedTorque * inverseInertia * deltaTime);
		angularVelocity = angularVelocity * std::pow(angularDrag, deltaTime * 60.0f);
		if (std::abs(angularVelocity) < 0.01f) angularVelocity = 0.0f;

		transform.Rotate(RAD2DEG(angularVelocity) * deltaTime);

		accumulatedForces = vec2(0, 0);
		accumulatedTorque = 0.0f;
	}

	void Rigidbody::ApplyGravity(const vec2& gravity) noexcept {
		accumulatedForces = accumulatedForces + gravity * gravityScale * mass;
	}

	void Rigidbody::ApplyForce(vec2 force) noexcept {
		accumulatedForces = accumulatedForces + force;
	}

	void Rigidbody::ApplyImpulse(vec2 impulse) noexcept {
		velocity = velocity + (impulse * inverseMass);
	}

	void Rigidbody::ApplyImpulseAtPosition(vec2 impulse, Point2D position, float moi) noexcept {
		vec2 r = position - transform.position;
		float crossProduct = r.x * impulse.y - r.y * impulse.x;
		if (moi > 0.0f && inverseMass > 0.0f) {
			angularVelocity += crossProduct / moi;
		}
		ApplyImpulse(impulse);
	}

	void Rigidbody::ApplyTorque(float torque) noexcept {
		accumulatedTorque = accumulatedTorque + torque;
	}

	void Rigidbody::ApplyForceAtPosition(vec2 force, Point2D position) noexcept {
		vec2 r = position - transform.position;
		accumulatedForces = accumulatedForces + force;
		accumulatedTorque = accumulatedTorque + Cross(r, force);
	}

} // namespace elysian
