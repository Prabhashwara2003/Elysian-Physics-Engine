#include "CollisionResolver.h"
#include <cmath>

namespace elysian {

CollisionResolver::CollisionResolver() {}

void CollisionResolver::Resolve(CollisionInfo& info) {
    // 1. Calculate radii
    vec2 rA = info.collisionPoint - info.rigidbodyA.transform->position;
    vec2 rB = info.collisionPoint - info.rigidbodyB.transform->position;

    // 2. Relative velocity at contact point
    vec2 vA = info.rigidbodyA.velocity + Cross(info.rigidbodyA.angularVelocity, rA);
    vec2 vB = info.rigidbodyB.velocity + Cross(info.rigidbodyB.angularVelocity, rB);
    vec2 relativeVelocity = vB - vA;
    float velocityAlongNormal = Dot(relativeVelocity, info.normal);

    // 3. Separate normal and tangential velocities
    vec2 normalVelocity = info.normal * velocityAlongNormal;
    vec2 tangentialVelocity = relativeVelocity - normalVelocity;

    if (velocityAlongNormal > 0) return;

    // 4. Restitution
    float restitution = fminf(info.rigidbodyA.bounciness, info.rigidbodyB.bounciness);

    // 5. Rotational denominator
    float rACrossN = rA.x * info.normal.y - rA.y * info.normal.x;
    float rBCrossN = rB.x * info.normal.y - rB.y * info.normal.x;

    float invMassSum = info.rigidbodyA.inverseMass + info.rigidbodyB.inverseMass;
    float angularTermA = (rACrossN * rACrossN) / info.colliderA.momentOfInertia;
    float angularTermB = (rBCrossN * rBCrossN) / info.colliderB.momentOfInertia;

    // 6. Normal impulse scalar
    float impulseScalar = -(1.0f + restitution) * velocityAlongNormal;
    impulseScalar /= (invMassSum + angularTermA + angularTermB);

    vec2 normalImpulse = info.normal * impulseScalar;

    // 7. Friction impulse
    float frictionCoeff = sqrtf(info.rigidbodyA.friction * info.rigidbodyB.friction);
    vec2 tangent = vec2(-info.normal.y, info.normal.x);
    if (Dot(tangentialVelocity, tangent) < 0) {
        tangent = tangent * -1.0f;
    }
    float tangentSpeed = Magnitude(tangentialVelocity);
    float frictionImpulseScalar = 0.0f;
    if (tangentSpeed > 0.0f) {
        float rACrossT = rA.x * tangent.y - rA.y * tangent.x;
        float rBCrossT = rB.x * tangent.y - rB.y * tangent.x;
        float angularTermAT = (rACrossT * rACrossT) / info.colliderA.momentOfInertia;
        float angularTermBT = (rBCrossT * rBCrossT) / info.colliderB.momentOfInertia;

        frictionImpulseScalar = -tangentSpeed / (invMassSum + angularTermAT + angularTermBT);

        float maxFriction = fabsf(impulseScalar) * frictionCoeff;
        frictionImpulseScalar = fmaxf(-maxFriction, fminf(frictionImpulseScalar, maxFriction));
    }
    vec2 frictionImpulse = tangent * frictionImpulseScalar;

    // 8. Total impulse
    vec2 totalImpulse = normalImpulse + frictionImpulse;

    // 9. Apply impulse
    info.rigidbodyA.ApplyImpulseAtPosition(totalImpulse * (-1.0f), info.collisionPoint, info.colliderA.momentOfInertia);
    info.rigidbodyB.ApplyImpulseAtPosition(totalImpulse, info.collisionPoint, info.colliderB.momentOfInertia);

    // 10. Positional correction (prevents sinking)
    const float percent = 0.2f;
    const float slop = 0.01f;
    float correctionMag = fmaxf(info.penetrationDepth - slop, 0.0f) / invMassSum * percent;
    vec2 correction = info.normal * correctionMag;

    info.rigidbodyA.transform->position = info.rigidbodyA.transform->position - correction * info.rigidbodyA.inverseMass;
    info.rigidbodyB.transform->position = info.rigidbodyB.transform->position + correction * info.rigidbodyB.inverseMass;
}

} // namespace elysian