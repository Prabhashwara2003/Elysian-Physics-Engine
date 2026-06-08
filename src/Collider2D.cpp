#include "Collider2D.h"
#include <cfloat>
#include <cmath>

namespace elysian {

Collider2D::~Collider2D() {}

Collider2D::Collider2D(Transform* transform) 
	: transform(transform)
	, rigidbody(nullptr)
{}

CircleCollider::CircleCollider(Circle* circle, Transform* transform) 
	:circle(circle),Collider2D(transform)
{
	this->momentOfInertia = (circle->radius * circle->radius) * 0.5f;
}

void CircleCollider::SyncTransform() {
	circle->Position = transform->position;
}

Rectangle2D CircleCollider::getAABB() {
	vec2 min = circle->Position - vec2(circle->radius, circle->radius);
	vec2 size = vec2(2 * circle->radius, 2 * circle->radius);

	return Rectangle2D(min, size);
}

BoxCollider::BoxCollider(OrientedRectangle* rectangle, Transform* transform)
	:rectangle(rectangle),Collider2D(transform)
{
	vec2 temp = rectangle->halfExtents * 2;
	this->momentOfInertia = Dot(temp, temp);
}

void BoxCollider::SyncTransform() {
	rectangle->position = transform->position;
	rectangle->rotation = transform->rotation;
}

Rectangle2D BoxCollider::getAABB() {
	vec2 half = rectangle->halfExtents;
	vec2 center = rectangle->position;
	float angle = DEG2RAD(rectangle->rotation);
	float zRotation2X2[] = {cosf(angle), sinf(angle), -sinf(angle), cosf(angle)};

	vec2 corners[4] = {
		vec2(-half.x, -half.y),
		vec2( half.x, -half.y),
		vec2( half.x,  half.y),
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
