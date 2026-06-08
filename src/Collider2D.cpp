#include "Collider2D.h"

Collider2D::Collider2D(Transform* transform) 
	:transform(transform)
{}

CircleCollider::CircleCollider(Circle* circle, Transform* transform) 
	:circle(circle),Collider2D(transform)
{
	this-> momentOfInertia = (circle->radius * circle->radius) * 0.5;
}

AABB CircleCollider::getAABB() {
	vec2 min = vec2(circle->Position - vec2(circle->radius, circle->radius));
	vec2 max = vec2(circle->Position + vec2(circle->radius, circle->radius));

	return AABB(min, max);
}

BoxCollider::BoxCollider(OrientedRectangle* rectangle, Transform* transform)
	:rectangle(rectangle),Collider2D(transform)
{
	vec2 temp = rectangle->halfExtents * 2;
	this->momentOfInertia = Dot(temp,temp);
}

AABB BoxCollider::getAABB() {

	vec2 v1 = rectangle->position + rectangle->halfExtents;
	vec2 v2 = rectangle->position - rectangle->halfExtents;
	vec2 v3 = vec2(v1.x , v2.y);
	vec2 v4 = vec2(v2.x, v1.y);

	float angle = DEG2RAD(rectangle->rotation);
	float zRotation2X2[] = {cosf(angle),sinf(angle),-sinf(angle),cosf(angle)};

	Multiply(v1.asArray, v1.asArray, 2, 1, zRotation2X2, 2, 2);
	Multiply(v1.asArray, v1.asArray, 2, 1, zRotation2X2, 2, 2);
	Multiply(v1.asArray, v1.asArray, 2, 1, zRotation2X2, 2, 2);
	Multiply(v1.asArray, v1.asArray, 2, 1, zRotation2X2, 2, 2);

	float minx = fminf(fminf(v1.x, v2.x), fminf(v3.x, v4.x));
	float miny = fminf(fminf(v1.y, v2.y), fminf(v3.y, v4.y));
	float maxx = fmaxf(fmaxf(v1.x, v2.x), fmaxf(v3.x, v4.x));
	float maxy = fmaxf(fmaxf(v1.y, v2.y), fmaxf(v3.y, v4.y));

	vec2 max = vec2(maxx,maxy);
	vec2 min = vec2(minx, miny);

	return AABB(min, max);
}
