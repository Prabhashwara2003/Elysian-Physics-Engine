#pragma once
#ifndef _H_RIGIDBODY
#define _H_RIGIDBODY

#include "PhysicsEngine/Export.h"
#include "Geometry2D.h"
#include "Transform.h"

namespace elysian {

class PHYSICSENGINE_API Rigidbody
{
public:
	float mass;
	float inverseMass;
	float momentOfInertia;
	float inverseInertia;

	vec2  accumulatedForces;
	float accumulatedTorque;
	vec2  impulses;
	bool  isGravityOn;
	vec2  acceleration;
	vec2  velocity;
	float angularVelocity;
	float drag;
	float angularDrag;
	Transform transform;
	float bounciness;
	float friction;
	float gravityScale;

	Rigidbody(vec2 position, float rotation, vec2 scale) noexcept;
	virtual ~Rigidbody() = default;

	Rigidbody(const Rigidbody&) = delete;
	Rigidbody& operator=(const Rigidbody&) = delete;
	Rigidbody(Rigidbody&&) = delete;
	Rigidbody& operator=(Rigidbody&&) = delete;

	void Integrate(float deltaTime) noexcept;
	void ApplyForce(vec2 force) noexcept;
	void ApplyImpulse(vec2 impulse) noexcept;
	void ApplyImpulseAtPosition(vec2 impulse, Point2D position, float momentOfInertia) noexcept;
	void ApplyForceAtPosition(vec2 force, Point2D position) noexcept;
	void ApplyTorque(float torque) noexcept;
	void ApplyGravity(const vec2& gravity) noexcept;
};

} // namespace elysian

#endif // !_H_RIGIDBODY
