#include "Collider2D.h"

Collider2D::Collider2D(Transform* transform) 
	:transform(transform)
{}


CircleCollider::CircleCollider(Circle* circle, Transform* transform) 
	:circle(circle),Collider2D(transform)
{}


