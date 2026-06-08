#pragma once
#include "Transform.h"
#include "Geometry2D.h"
#include "matrices.h"
#include "vectors.h"
#include "ShapeTypes.h"
#include "Rigidbody.h"

namespace elysian {

class Collider2D 
{
public:
	Transform* transform;
	Rigidbody* rigidbody;
	float momentOfInertia;
	Shape shape;

	virtual Rectangle2D getAABB() = 0;
	virtual void SyncTransform() = 0;
	Collider2D(Transform* transform);
	virtual ~Collider2D();
};

class CircleCollider :public Collider2D {
public:
	Circle* circle;
	
	CircleCollider(Circle* circle,Transform* transform);
	Rectangle2D getAABB() override;
	void SyncTransform() override;
};

class BoxCollider :public Collider2D {
public:
	OrientedRectangle* rectangle;

	BoxCollider(OrientedRectangle* rectangle,Transform* transform);
	Rectangle2D getAABB() override;
	void SyncTransform() override;
};

} // namespace elysian