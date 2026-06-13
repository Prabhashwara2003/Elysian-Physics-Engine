#include "CollisionDetector.h"
#include <cfloat>
#include <cmath>

namespace elysian {

    std::unique_ptr<CollisionInfo> CollisionDetector::Detect(Collider2D* a, Collider2D* b) noexcept {
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

    std::unique_ptr<CollisionInfo> CollisionDetector::CircleVsCircle(CircleCollider* a, CircleCollider* b) noexcept {
        Circle& c1 = *a->circle;
        Circle& c2 = *b->circle;

        vec2 diff = c2.Position - c1.Position;
        float distSqr = Magnitudesqr(diff);
        float radiusSum = c1.radius + c2.radius;

        if (distSqr >= radiusSum * radiusSum) return nullptr;

        float distance = std::sqrt(distSqr);

        auto info = std::make_unique<CollisionInfo>(a, b, a->rigidbody, b->rigidbody);
        info->normal = (distance != 0) ? Normalized(diff) : vec2(1, 0);
        info->penetrationDepth = radiusSum - distance;
        info->collisionPoint = c1.Position + info->normal * c1.radius;
        info->hasCollision = true;
        return info;
    }

    static void GetWorldVerts(const OrientedRectangle& r, vec2 out[4]) {
        float theta = DEG2RAD(r.rotation);
        float zRot[] = { std::cos(theta), std::sin(theta), -std::sin(theta), std::cos(theta) };
        vec2 local[4] = {
            vec2(-r.halfExtents.x, -r.halfExtents.y),
            vec2(r.halfExtents.x, -r.halfExtents.y),
            vec2(r.halfExtents.x,  r.halfExtents.y),
            vec2(-r.halfExtents.x,  r.halfExtents.y)
        };
        for (int i = 0; i < 4; i++) {
            Multiply(out[i].asArray, local[i].asArray, 1, 2, zRot, 2, 2);
            out[i] = out[i] + r.position;
        }
    }

    std::unique_ptr<CollisionInfo> CollisionDetector::BoxVsBox(BoxCollider* a, BoxCollider* b) noexcept {
        OrientedRectangle& r1 = *a->rectangle;
        OrientedRectangle& r2 = *b->rectangle;

        float theta1 = DEG2RAD(r1.rotation);
        float theta2 = DEG2RAD(r2.rotation);
        float zRot1[] = { std::cos(theta1), std::sin(theta1), -std::sin(theta1), std::cos(theta1) };
        float zRot2[] = { std::cos(theta2), std::sin(theta2), -std::sin(theta2), std::cos(theta2) };

        vec2 axisToTest[4];
        vec2 axis;

        axis = Normalized(vec2(1, 0));
        Multiply(axisToTest[0].asArray, axis.asArray, 1, 2, zRot1, 2, 2);

        axis = Normalized(vec2(0, 1));
        Multiply(axisToTest[1].asArray, axis.asArray, 1, 2, zRot1, 2, 2);

        axis = Normalized(vec2(1, 0));
        Multiply(axisToTest[2].asArray, axis.asArray, 1, 2, zRot2, 2, 2);

        axis = Normalized(vec2(0, 1));
        Multiply(axisToTest[3].asArray, axis.asArray, 1, 2, zRot2, 2, 2);

        float minDepth = FLT_MAX;
        vec2  minAxis;

        for (int i = 0; i < 4; i++) {
            Interval2D intervalA = GetInterval(r1, axisToTest[i]);
            Interval2D intervalB = GetInterval(r2, axisToTest[i]);

            if (!(intervalB.min <= intervalA.max && intervalA.min <= intervalB.max))
                return nullptr;

            float overlap = fminf(intervalA.max, intervalB.max)
                - fmaxf(intervalA.min, intervalB.min);
            if (overlap < minDepth) {
                minDepth = overlap;
                minAxis = axisToTest[i];
            }
        }

        vec2 diff = r2.position - r1.position;
        if (Dot(diff, minAxis) < 0) minAxis = minAxis * -1.0f;

        vec2 verts2[4];
        GetWorldVerts(r2, verts2);

        float deepest = FLT_MAX;
        for (int i = 0; i < 4; i++) {
            float p = Dot(verts2[i], minAxis);
            if (p < deepest) deepest = p;
        }

        const float tolerance = 0.5f;
        vec2 contactSum(0, 0);
        int  contactCount = 0;
        for (int i = 0; i < 4; i++) {
            float p = Dot(verts2[i], minAxis);
            if (p <= deepest + tolerance) {
                contactSum = contactSum + verts2[i];
                contactCount++;
            }
        }

        vec2 contactPoint = contactSum * (1.0f / (float)contactCount);

        auto info = std::make_unique<CollisionInfo>(a, b, a->rigidbody, b->rigidbody);
        info->normal = minAxis;
        info->penetrationDepth = minDepth;
        info->collisionPoint = contactPoint;
        info->hasCollision = true;
        return info;
    }

    std::unique_ptr<CollisionInfo> CollisionDetector::CircleVsBox(CircleCollider* circle, BoxCollider* box) noexcept {
        OrientedRectangle& rect = *box->rectangle;
        Circle& c = *circle->circle;

        vec2 rotVector = c.Position - rect.position;
        float theta = DEG2RAD(rect.rotation);
        float zRot[] = { std::cos(theta), -std::sin(theta), std::sin(theta), std::cos(theta) };
        Multiply(rotVector.asArray, vec2(rotVector.x, rotVector.y).asArray, 1, 2, zRot, 2, 2);

        vec2 localCenter = rotVector + rect.halfExtents;
        Rectangle2D localRect(Point2D(), rect.halfExtents * 2.0f);

        vec2 min = GetMin(localRect);
        vec2 max = GetMax(localRect);

        vec2 closest = localCenter;
        CLAMP(closest.x, min.x, max.x);
        CLAMP(closest.y, min.y, max.y);

        vec2  toCircle = localCenter - closest;
        float distSqr = Magnitudesqr(toCircle);

        if (distSqr > c.radius * c.radius) return nullptr;

        float distance = std::sqrt(distSqr);
        bool circleInsideBox = (distance == 0);

        vec2 localNormal;
        if (!circleInsideBox) {
            localNormal = Normalized(toCircle);
        }
        else {
            float dx = fminf(localCenter.x - min.x, max.x - localCenter.x);
            float dy = fminf(localCenter.y - min.y, max.y - localCenter.y);
            if (dx < dy) {
                localNormal = vec2(localCenter.x < (min.x + max.x) * 0.5f ? -1.0f : 1.0f, 0);
                closest.x = (localNormal.x < 0) ? min.x : max.x;
            }
            else {
                localNormal = vec2(0, localCenter.y < (min.y + max.y) * 0.5f ? -1.0f : 1.0f);
                closest.y = (localNormal.y < 0) ? min.y : max.y;
            }
        }

        float thetaBack = DEG2RAD(rect.rotation);
        float zRotBack[] = { std::cos(thetaBack), std::sin(thetaBack), -std::sin(thetaBack), std::cos(thetaBack) };
        vec2 worldNormal;
        Multiply(worldNormal.asArray, localNormal.asArray, 1, 2, zRotBack, 2, 2);

        vec2 localContact = closest - rect.halfExtents;
        vec2 worldContact;
        Multiply(worldContact.asArray, localContact.asArray, 1, 2, zRotBack, 2, 2);
        worldContact = worldContact + rect.position;

        auto info = std::make_unique<CollisionInfo>(circle, box, circle->rigidbody, box->rigidbody);

        if (!circleInsideBox) {
            info->normal = worldNormal * -1.0f;
            info->penetrationDepth = c.radius - distance;
        }
        else {
            info->normal = worldNormal;
            float embeddedDist = Magnitude(vec2(closest.x - localCenter.x, closest.y - localCenter.y));
            info->penetrationDepth = c.radius + embeddedDist;
        }

        info->collisionPoint = worldContact;
        info->hasCollision = true;
        return info;
    }

} // namespace elysian
