#pragma once
#include "Collider2D.h"
#include "CollisionInfo.h"

namespace elysian {

class CollisionDetector
{
public:

	CollisionDetector();
	CollisionInfo* Detect(Collider2D* a, Collider2D* b);
	CollisionInfo* CircleVsCircle(CircleCollider* a, CircleCollider* b);
	CollisionInfo* CircleVsBox(CircleCollider* circle, BoxCollider* box);
	CollisionInfo* BoxVsBox(BoxCollider* a, BoxCollider* b);
};

} // namespace elysian

