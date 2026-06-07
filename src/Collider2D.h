#pragma once
#include"Transform.h"
#include "AABB.h" 
#include "Geometry2D.h"

class Collider2D 
{
public:
	Transform* transform;

	virtual AABB getAABB() = 0;
	Collider2D(Transform* tarnsform);
	virtual ~Collider2D();
};

class CircleCollider :public Collider2D {
	
public:
	Circle* circle;

	CircleCollider(Circle* circle,Transform* transform);
	AABB getAABB();
};

class BoxCollider :public Collider2D {

public:
	Rectangle2D* rectangle;

	BoxCollider(Rectangle2D* rectangle,Transform* transform);
	AABB getAABB();
};