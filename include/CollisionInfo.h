#pragma once
#include "PhysicsEngine/Export.h"
#include "Collider2D.h"
#include "Rigidbody.h"

namespace elysian {

class PHYSICSENGINE_API CollisionInfo {
public:
    CollisionInfo(Collider2D* a, Collider2D* b, Rigidbody* rbA, Rigidbody* rbB) noexcept
        : colliderA(a), colliderB(b), rigidbodyA(rbA), rigidbodyB(rbB) {}

    CollisionInfo() = default;

    Collider2D* colliderA = nullptr;
    Collider2D* colliderB = nullptr;
    Rigidbody* rigidbodyA = nullptr;
    Rigidbody* rigidbodyB = nullptr;
    vec2 normal;
    Point2D collisionPoint;
    float penetrationDepth = 0.0f;
    bool hasCollision = false;
};

} // namespace elysian
