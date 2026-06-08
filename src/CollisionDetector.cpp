#include "CollisionDetector.h"
#include <cfloat>
#include <cmath>

namespace elysian {

CollisionDetector::CollisionDetector() {

}

CollisionInfo* CollisionDetector::Detect(Collider2D* a, Collider2D* b) {
    if (!a->rigidbody || !b->rigidbody) return nullptr;
    if (!a->rigidbody->inverseMass && !b->rigidbody->inverseMass) return nullptr;

    CircleCollider* ca = dynamic_cast<CircleCollider*>(a);
    CircleCollider* cb = dynamic_cast<CircleCollider*>(b);
    if (ca && cb) return CircleVsCircle(ca, cb);

    BoxCollider* ba = dynamic_cast<BoxCollider*>(a);
    BoxCollider* bb = dynamic_cast<BoxCollider*>(b);
    if (ba && bb) return BoxVsBox(ba, bb);

    CircleCollider* c = dynamic_cast<CircleCollider*>(a);
    BoxCollider* box = dynamic_cast<BoxCollider*>(b);
    if (c && box) return CircleVsBox(c, box);

    CircleCollider* c2 = dynamic_cast<CircleCollider*>(b);
    BoxCollider* box2 = dynamic_cast<BoxCollider*>(a);
    if (c2 && box2) return CircleVsBox(c2, box2);

    return nullptr;
}

CollisionInfo* CollisionDetector::CircleVsCircle(CircleCollider* a, CircleCollider* b) {
    Circle& c1 = *a->circle;
    Circle& c2 = *b->circle;

    vec2 diff = c2.Position - c1.Position;
    float distSqr = Magnitudesqr(diff);
    float radiusSum = c1.radius + c2.radius;

    if (distSqr >= radiusSum * radiusSum) return nullptr;

    float distance = sqrtf(distSqr);

    CollisionInfo* info = new CollisionInfo(*a, *b, *a->rigidbody, *b->rigidbody);
    info->normal = (distance != 0) ? Normalized(diff) : vec2(1, 0);
    info->penetrationDepth = radiusSum - distance;
    info->collisionPoint = c1.Position + info->normal * c1.radius;
    info->hasCollision = true;
    return info;
}

CollisionInfo* CollisionDetector::BoxVsBox(BoxCollider* a, BoxCollider* b) {
    OrientedRectangle& r1 = *a->rectangle;
    OrientedRectangle& r2 = *b->rectangle;

    // Same axes as your RectangleOrientedRectangle(OrientedRectangle, OrientedRectangle)
    float theta1 = DEG2RAD(r1.rotation);
    float theta2 = DEG2RAD(r2.rotation);
    float zRot1[] = { cosf(theta1), sinf(theta1), -sinf(theta1), cosf(theta1) };
    float zRot2[] = { cosf(theta2), sinf(theta2), -sinf(theta2), cosf(theta2) };

    vec2 axisToTest[4];
    vec2 axis;

    axis = Normalized(vec2(r1.halfExtents.x, 0));
    Multiply(axisToTest[0].asArray, axis.asArray, 1, 2, zRot1, 2, 2);

    axis = Normalized(vec2(0, r1.halfExtents.y));
    Multiply(axisToTest[1].asArray, axis.asArray, 1, 2, zRot1, 2, 2);

    axis = Normalized(vec2(r2.halfExtents.x, 0));
    Multiply(axisToTest[2].asArray, axis.asArray, 1, 2, zRot2, 2, 2);

    axis = Normalized(vec2(0, r2.halfExtents.y));
    Multiply(axisToTest[3].asArray, axis.asArray, 1, 2, zRot2, 2, 2);

    // Find minimum overlap axis (same as SAT but track depth)
    float minDepth = FLT_MAX;
    vec2  minAxis;

    for (int i = 0; i < 4; i++) {
        Interval2D intervalA = GetInterval(r1, axisToTest[i]);
        Interval2D intervalB = GetInterval(r2, axisToTest[i]);

        if (!(intervalB.min <= intervalA.max && intervalA.min <= intervalB.max))
            return nullptr; // separating axis found

        float overlap = fminf(intervalA.max, intervalB.max)
            - fmaxf(intervalA.min, intervalB.min);
        if (overlap < minDepth) {
            minDepth = overlap;
            minAxis = axisToTest[i];
        }
    }

    // Make sure normal points from a to b
    vec2 diff = r2.position - r1.position;
    if (Dot(diff, minAxis) < 0) minAxis = minAxis * -1.0f;

    CollisionInfo* info = new CollisionInfo(*a, *b, *a->rigidbody, *b->rigidbody);
    info->normal = minAxis;
    info->penetrationDepth = minDepth;
    info->collisionPoint = r1.position + minAxis * minDepth;
    info->hasCollision = true;
    return info;
}

CollisionInfo* CollisionDetector::CircleVsBox(CircleCollider* circle, BoxCollider* box) {
    OrientedRectangle& rect = *box->rectangle;
    Circle& c = *circle->circle;

    // Same local space transform as your CircleOrientedRectangle()
    vec2 rotVector = c.Position - rect.position;
    float theta = -DEG2RAD(rect.rotation);
    float zRot[] = { cosf(theta), sinf(theta), -sinf(theta), cosf(theta) };
    Multiply(rotVector.asArray, vec2(rotVector.x, rotVector.y).asArray, 1, 2, zRot, 2, 2);

    // Local space circle and rect (same as your implementation)
    vec2 localCenter = rotVector + rect.halfExtents;
    Rectangle2D localRect(Point2D(), rect.halfExtents * 2.0f);

    vec2 min = GetMin(localRect);
    vec2 max = GetMax(localRect);

    vec2 closest = localCenter;
    CLAMP(closest.x, min.x, max.x);
    CLAMP(closest.y, min.y, max.y);

    vec2  toCircle = localCenter - closest;
    float distSqr = LengthSqr(Line2D(localCenter, closest));

    if (distSqr > c.radius * c.radius) return nullptr;

    float distance = sqrtf(distSqr);

    // Local space normal
    vec2 localNormal = (distance != 0) ? Normalized(toCircle) : vec2(1, 0);

    // Rotate normal back to world space
    float thetaBack = DEG2RAD(rect.rotation);
    float zRotBack[] = { cosf(thetaBack), sinf(thetaBack), -sinf(thetaBack), cosf(thetaBack) };
    vec2 worldNormal;
    Multiply(worldNormal.asArray, localNormal.asArray, 1, 2, zRotBack, 2, 2);

    // Contact point is the closest point in world space
    vec2 localContact = closest - rect.halfExtents; // undo the offset
    vec2 worldContact;
    Multiply(worldContact.asArray, localContact.asArray, 1, 2, zRotBack, 2, 2);
    worldContact = worldContact + rect.position;

    CollisionInfo* info = new CollisionInfo(*circle, *box, *circle->rigidbody, *box->rigidbody);
    info->normal = worldNormal;
    info->penetrationDepth = c.radius - distance;
    info->collisionPoint = worldContact;
    info->hasCollision = true;
    return info;
}

} // namespace elysian
