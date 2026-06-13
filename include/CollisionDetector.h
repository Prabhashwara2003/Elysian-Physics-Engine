#pragma once
#include "PhysicsEngine/Export.h"
#include <memory>
#include "Collider2D.h"
#include "CollisionInfo.h"

namespace elysian {

class PHYSICSENGINE_API CollisionDetector
{
public:
	CollisionDetector() = default;

	std::unique_ptr<CollisionInfo> Detect(Collider2D* a, Collider2D* b) noexcept;
	std::unique_ptr<CollisionInfo> CircleVsCircle(CircleCollider* a, CircleCollider* b) noexcept;
	std::unique_ptr<CollisionInfo> CircleVsBox(CircleCollider* circle, BoxCollider* box) noexcept;
	std::unique_ptr<CollisionInfo> BoxVsBox(BoxCollider* a, BoxCollider* b) noexcept;
};

} // namespace elysian
