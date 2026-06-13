#include "Collider2D.h"
#include <cfloat>
#include <cmath>

namespace elysian {

	Collider2D::Collider2D(Transform* transform, Shape shape) noexcept
		: transform(transform)
		, rigidbody(nullptr)
		, shape(shape)
		, momentOfInertia(1.0f)
	{
	}

	// --- CircleCollider ---

	CircleCollider::CircleCollider(Circle* circle, Transform* transform) noexcept
		: circle(circle), Collider2D(transform, Shape::circle)
	{
	}

	void CircleCollider::ComputeInertia() {
		float mass = (rigidbody && rigidbody->inverseMass > 0.0f)
			? 1.0f / rigidbody->inverseMass
			: 1.0f;
		momentOfInertia = 0.5f * mass * (circle->radius * circle->radius);
		if (momentOfInertia <= 0.0f) momentOfInertia = 1.0f;
	}

	void CircleCollider::SyncTransform() {
		circle->Position = transform->position;
	}

	Rectangle2D CircleCollider::GetAABB() {
		vec2 min = circle->Position - vec2(circle->radius, circle->radius);
		vec2 size = vec2(2.0f * circle->radius, 2.0f * circle->radius);
		return Rectangle2D(min, size);
	}

	// --- BoxCollider ---

	BoxCollider::BoxCollider(OrientedRectangle* rectangle, Transform* transform) noexcept
		: rectangle(rectangle), Collider2D(transform, Shape::box)
	{
	}

	void BoxCollider::ComputeInertia() {
		float mass = (rigidbody && rigidbody->inverseMass > 0.0f)
			? 1.0f / rigidbody->inverseMass
			: 1.0f;
		float w = rectangle->halfExtents.x * 2.0f;
		float h = rectangle->halfExtents.y * 2.0f;
		momentOfInertia = (mass / 12.0f) * (w * w + h * h);
		if (momentOfInertia <= 0.0f) momentOfInertia = 1.0f;
	}

	void BoxCollider::SyncTransform() {
		rectangle->position = transform->position;
		rectangle->rotation = transform->rotation;
	}

	Rectangle2D BoxCollider::GetAABB() {
		vec2 half = rectangle->halfExtents;
		vec2 center = rectangle->position;
		float angle = DEG2RAD(rectangle->rotation);
		float zRotation2X2[] = { std::cos(angle), std::sin(angle), -std::sin(angle), std::cos(angle) };

		vec2 corners[4] = {
			vec2(-half.x, -half.y),
			vec2(half.x, -half.y),
			vec2(half.x,  half.y),
			vec2(-half.x,  half.y)
		};

		float minx = FLT_MAX, miny = FLT_MAX, maxx = -FLT_MAX, maxy = -FLT_MAX;
		for (int i = 0; i < 4; i++) {
			vec2 rotated;
			Multiply(rotated.asArray, corners[i].asArray, 1, 2, zRotation2X2, 2, 2);
			rotated = rotated + center;
			if (rotated.x < minx) minx = rotated.x;
			if (rotated.y < miny) miny = rotated.y;
			if (rotated.x > maxx) maxx = rotated.x;
			if (rotated.y > maxy) maxy = rotated.y;
		}

		return Rectangle2D(vec2(minx, miny), vec2(maxx - minx, maxy - miny));
	}

} // namespace elysian
