#pragma once
#include "PhysicsEngine/Export.h"
#include "Transform.h"
#include "Geometry2D.h"
#include "matrices.h"
#include "vectors.h"
#include "ShapeTypes.h"
#include "Rigidbody.h"

namespace elysian {

class PHYSICSENGINE_API Collider2D
{
public:
	Transform* transform;
	Rigidbody* rigidbody;
	float momentOfInertia;
	Shape shape;

	virtual Rectangle2D GetAABB() = 0;
	virtual void SyncTransform() = 0;
	virtual void ComputeInertia() = 0;

	Collider2D(Transform* transform, Shape shape) noexcept;
	virtual ~Collider2D() = default;

	Collider2D(const Collider2D&) = delete;
	Collider2D& operator=(const Collider2D&) = delete;
};

class PHYSICSENGINE_API CircleCollider : public Collider2D {
public:
	Circle* circle;

	CircleCollider(Circle* circle, Transform* transform) noexcept;
	Rectangle2D GetAABB() override;
	void SyncTransform() override;
	void ComputeInertia() override;
};

class PHYSICSENGINE_API BoxCollider : public Collider2D {
public:
	OrientedRectangle* rectangle;

	BoxCollider(OrientedRectangle* rectangle, Transform* transform) noexcept;
	Rectangle2D GetAABB() override;
	void SyncTransform() override;
	void ComputeInertia() override;
};

} // namespace elysian
