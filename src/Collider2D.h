#pragma once
#include"Transform.h"
#include "AABB.h" 
#include "Geometry2D.h"
#include "matrices.h"
#include "vectors.h"
#include "ShapeTypes.h"

class Collider2D 
{
public:
	Transform* transform;
	float momentOfInertia;
	Shape shape;

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
	OrientedRectangle* rectangle;

	BoxCollider(OrientedRectangle* rectangle,Transform* transform);
	AABB getAABB();
};