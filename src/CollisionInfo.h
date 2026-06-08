#pragma once
#include "Collider2D.h"
#include "Rigidbody.h"

namespace elysian {

class CollisionInfo {
public:
    CollisionInfo(Collider2D& a, Collider2D& b, Rigidbody& rbA, Rigidbody& rbB)
        : colliderA(a), colliderB(b), rigidbodyA(rbA), rigidbodyB(rbB) {
    }

    Collider2D& colliderA;
    Collider2D& colliderB;
    vec2 normal;
    Point2D collisionPoint;
    Rigidbody& rigidbodyA;
    Rigidbody& rigidbodyB;
    float penetrationDepth = 0.0f;
    bool hasCollision = false;
};

} // namespace elysian