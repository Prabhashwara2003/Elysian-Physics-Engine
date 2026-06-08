#include "CollisionResolver.h"

void CollisionResolver::Resolve(CollisionInfo& info) {
    // 1. Calculate radii
    vec2 rA = info.collisionPoint - info.rigidbodyA.transform->position;
    vec2 rB = info.collisionPoint - info.rigidbodyB.transform->position;

    // 2. Relative velocity at contact point
    vec2 vA = info.rigidbodyA.velocity + Cross(info.rigidbodyA.angularVelocity, rA);
    vec2 vB = info.rigidbodyB.velocity + Cross(info.rigidbodyB.angularVelocity, rB);
    vec2 relativeVelocity = vB - vA;
    float velocityAlongNormal = Dot(relativeVelocity, info.normal);

    if (velocityAlongNormal > 0) return;

    // 3. Restitution
    float restitution = fminf(info.rigidbodyA.bounciness, info.rigidbodyB.bounciness);

    // 4. Rotational denominator
    float rACrossN = rA.x * info.normal.y - rA.y * info.normal.x;
    float rBCrossN = rB.x * info.normal.y - rB.y * info.normal.x;

    float invMassSum = info.rigidbodyA.inverseMass + info.rigidbodyB.inverseMass;
    float angularTermA = (rACrossN * rACrossN) / info.colliderA.momentOfInertia;
    float angularTermB = (rBCrossN * rBCrossN) / info.colliderB.momentOfInertia;

    // 5. Impulse scalar
    float impulseScalar = -(1.0f + restitution) * velocityAlongNormal;
    impulseScalar /= (invMassSum + angularTermA + angularTermB);

    vec2 impulse = info.normal * impulseScalar;

    // 6. Apply impulse
    info.rigidbodyA.ApplyImpulseAtPosition(impulse * (-1.0f), info.collisionPoint, info.colliderA.momentOfInertia);
    info.rigidbodyB.ApplyImpulseAtPosition(impulse, info.collisionPoint, info.colliderB.momentOfInertia);

    // 7. Positional correction (prevents sinking)
    const float percent = 0.2f;
    const float slop = 0.01f;
    float correctionMag = fmaxf(info.penetrationDepth - slop, 0.0f) / invMassSum * percent;
    vec2 correction = info.normal * correctionMag;

    info.rigidbodyA.transform->position = info.rigidbodyA.transform->position - correction * info.rigidbodyA.inverseMass;
    info.rigidbodyB.transform->position = info.rigidbodyB.transform->position + correction * info.rigidbodyB.inverseMass;
}