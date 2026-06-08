#pragma once
#include "Collider2D.h"
#include "RigidBody.h"

class CollisionInfo
{
public:	
	Collider2D& colliderA;
	Collider2D& colliderB;
	vec2 normal;
	Point2D collisionPoint;
	Rigidbody& rigidbodyA;
	Rigidbody& rigidbodyB;
	float penetrationDepth;
};

