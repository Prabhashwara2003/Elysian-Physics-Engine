#include "TestMacros.h"
#include "PhysicsSystem.h"
#include "CollisionDetector.h"

using namespace elysian;

void suite_TestCollision() {
    // --- CircleVsCircle detection ---
    {
        TEST("CircleVsCircle - collision detected");
        Circle c1(vec2(0, 0), 5.0f);
        Circle c2(vec2(8, 0), 5.0f);

        Rigidbody rb1(vec2(0, 0), 0.0f, vec2(1, 1));
        Rigidbody rb2(vec2(8, 0), 0.0f, vec2(1, 1));

        CircleCollider col1(&c1, &rb1.transform);
        col1.rigidbody = &rb1;
        CircleCollider col2(&c2, &rb2.transform);
        col2.rigidbody = &rb2;

        CollisionDetector detector;
        auto info = detector.Detect(&col1, &col2);

        EXPECT_TRUE(info != nullptr);
        EXPECT_TRUE(info->hasCollision);
        PASS();
    }

    {
        TEST("CircleVsCircle - no collision");
        Circle c1(vec2(0, 0), 5.0f);
        Circle c2(vec2(100, 0), 5.0f);

        Rigidbody rb1(vec2(0, 0), 0.0f, vec2(1, 1));
        Rigidbody rb2(vec2(100, 0), 0.0f, vec2(1, 1));

        CircleCollider col1(&c1, &rb1.transform);
        col1.rigidbody = &rb1;
        CircleCollider col2(&c2, &rb2.transform);
        col2.rigidbody = &rb2;

        CollisionDetector detector;
        auto info = detector.Detect(&col1, &col2);

        EXPECT_TRUE(info == nullptr);
        PASS();
    }

    {
        TEST("CircleVsCircle - penetration depth");
        Circle c1(vec2(0, 0), 5.0f);
        Circle c2(vec2(6, 0), 5.0f);

        Rigidbody rb1(vec2(0, 0), 0.0f, vec2(1, 1));
        Rigidbody rb2(vec2(6, 0), 0.0f, vec2(1, 1));

        CircleCollider col1(&c1, &rb1.transform);
        col1.rigidbody = &rb1;
        CircleCollider col2(&c2, &rb2.transform);
        col2.rigidbody = &rb2;

        CollisionDetector detector;
        auto info = detector.Detect(&col1, &col2);

        EXPECT_TRUE(info != nullptr);
        EXPECT_NEAR(info->penetrationDepth, 4.0f, 0.01f);
        PASS();
    }

    // --- Static-static pairs filtered ---
    {
        TEST("Static-static pair returns nullptr");
        Circle c1(vec2(0, 0), 5.0f);
        Circle c2(vec2(3, 0), 5.0f);

        Rigidbody rb1(vec2(0, 0), 0.0f, vec2(1, 1));
        rb1.inverseMass = 0.0f;
        Rigidbody rb2(vec2(3, 0), 0.0f, vec2(1, 1));
        rb2.inverseMass = 0.0f;

        CircleCollider col1(&c1, &rb1.transform);
        col1.rigidbody = &rb1;
        CircleCollider col2(&c2, &rb2.transform);
        col2.rigidbody = &rb2;

        CollisionDetector detector;
        auto info = detector.Detect(&col1, &col2);

        EXPECT_TRUE(info == nullptr);
        PASS();
    }

    // --- BoxVsBox SAT ---
    {
        TEST("BoxVsBox - collision detected");
        OrientedRectangle r1(vec2(0, 0), vec2(5, 5));
        OrientedRectangle r2(vec2(6, 0), vec2(5, 5));

        Rigidbody rb1(vec2(0, 0), 0.0f, vec2(1, 1));
        Rigidbody rb2(vec2(6, 0), 0.0f, vec2(1, 1));

        BoxCollider col1(&r1, &rb1.transform);
        col1.rigidbody = &rb1;
        BoxCollider col2(&r2, &rb2.transform);
        col2.rigidbody = &rb2;

        CollisionDetector detector;
        auto info = detector.Detect(&col1, &col2);

        EXPECT_TRUE(info != nullptr);
        EXPECT_TRUE(info->hasCollision);
        PASS();
    }

    // --- PhysicsSystem basic step ---
    {
        TEST("PhysicsSystem step does not crash");
        PhysicsSystem physics;

        Circle circle(vec2(400, 100), 25.0f);
        Rigidbody ball(vec2(400, 100), 0.0f, vec2(1, 1));
        CircleCollider ballCollider(&circle, &ball.transform);
        ballCollider.rigidbody = &ball;

        physics.AddRigidbody(&ball);
        physics.AddCollider(&ballCollider);

        physics.Step(1.0f / 60.0f);

        EXPECT_TRUE(true);
        PASS();
    }

    // --- PhysicsSystem gravity test ---
    {
        TEST("PhysicsSystem applies gravity");
        PhysicsSystem physics;
        physics.SetGravity(vec2(0.0f, 100.0f));

        Circle circle(vec2(400, 100), 25.0f);
        Rigidbody ball(vec2(400, 100), 0.0f, vec2(1, 1));
        CircleCollider ballCollider(&circle, &ball.transform);
        ballCollider.rigidbody = &ball;

        physics.AddRigidbody(&ball);
        physics.AddCollider(&ballCollider);

        float initialY = ball.transform.position.y;
        physics.Step(1.0f / 60.0f);

        EXPECT_NEAR(ball.transform.position.y, initialY + 100.0f / (60.0f * 60.0f), 0.001f);
        PASS();
    }
}
