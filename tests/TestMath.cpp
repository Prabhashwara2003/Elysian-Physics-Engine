#include "TestMacros.h"
#include "vectors.h"
#include "matrices.h"

using namespace elysian;

void suite_TestMath() {
    // --- vec2 construction ---
    {
        TEST("vec2 default constructor");
        vec2 v;
        EXPECT_NEAR(v.x, 0.0f, 1e-6f);
        EXPECT_NEAR(v.y, 0.0f, 1e-6f);
        PASS();
    }

    {
        TEST("vec2 parameterized constructor");
        vec2 v(3.0f, 4.0f);
        EXPECT_NEAR(v.x, 3.0f, 1e-6f);
        EXPECT_NEAR(v.y, 4.0f, 1e-6f);
        PASS();
    }

    // --- vec2 arithmetic ---
    {
        TEST("vec2 addition");
        vec2 a(1, 2), b(3, 4);
        vec2 c = a + b;
        EXPECT_NEAR(c.x, 4.0f, 1e-6f);
        EXPECT_NEAR(c.y, 6.0f, 1e-6f);
        PASS();
    }

    {
        TEST("vec2 subtraction");
        vec2 a(5, 7), b(2, 3);
        vec2 c = a - b;
        EXPECT_NEAR(c.x, 3.0f, 1e-6f);
        EXPECT_NEAR(c.y, 4.0f, 1e-6f);
        PASS();
    }

    {
        TEST("vec2 scalar multiplication");
        vec2 a(2, 3);
        vec2 c = a * 2.0f;
        EXPECT_NEAR(c.x, 4.0f, 1e-6f);
        EXPECT_NEAR(c.y, 6.0f, 1e-6f);
        PASS();
    }

    {
        TEST("vec2 scalar multiplication (commuted)");
        vec2 a(2, 3);
        vec2 c = 2.0f * a;
        EXPECT_NEAR(c.x, 4.0f, 1e-6f);
        EXPECT_NEAR(c.y, 6.0f, 1e-6f);
        PASS();
    }

    {
        TEST("vec2 compound += ");
        vec2 a(1, 2);
        a += vec2(3, 4);
        EXPECT_NEAR(a.x, 4.0f, 1e-6f);
        EXPECT_NEAR(a.y, 6.0f, 1e-6f);
        PASS();
    }

    {
        TEST("vec2 compound -= ");
        vec2 a(5, 7);
        a -= vec2(2, 3);
        EXPECT_NEAR(a.x, 3.0f, 1e-6f);
        EXPECT_NEAR(a.y, 4.0f, 1e-6f);
        PASS();
    }

    {
        TEST("vec2 compound *= scalar");
        vec2 a(2, 3);
        a *= 2.0f;
        EXPECT_NEAR(a.x, 4.0f, 1e-6f);
        EXPECT_NEAR(a.y, 6.0f, 1e-6f);
        PASS();
    }

    {
        TEST("vec2 unary negation");
        vec2 a(2, -3);
        vec2 b = -a;
        EXPECT_NEAR(b.x, -2.0f, 1e-6f);
        EXPECT_NEAR(b.y, 3.0f, 1e-6f);
        PASS();
    }

    {
        TEST("vec2 equality");
        vec2 a(1, 2), b(1, 2);
        EXPECT_TRUE(a == b);
        PASS();
    }

    {
        TEST("vec2 inequality");
        vec2 a(1, 2), b(3, 4);
        EXPECT_TRUE(a != b);
        PASS();
    }

    // --- Dot product ---
    {
        TEST("Dot product");
        vec2 a(1, 0), b(0, 1);
        EXPECT_NEAR(Dot(a, b), 0.0f, 1e-6f);
        EXPECT_NEAR(Dot(a, a), 1.0f, 1e-6f);
        PASS();
    }

    // --- Cross product (scalar) ---
    {
        TEST("Cross product (2D)");
        vec2 a(1, 0), b(0, 1);
        EXPECT_NEAR(Cross(a, b), 1.0f, 1e-6f);
        EXPECT_NEAR(Cross(b, a), -1.0f, 1e-6f);
        PASS();
    }

    // --- Magnitude ---
    {
        TEST("Magnitude");
        vec2 v(3, 4);
        EXPECT_NEAR(Magnitude(v), 5.0f, 1e-6f);
        PASS();
    }

    {
        TEST("Magnitudesqr");
        vec2 v(3, 4);
        EXPECT_NEAR(Magnitudesqr(v), 25.0f, 1e-6f);
        PASS();
    }

    // --- Normalize ---
    {
        TEST("Normalize");
        vec2 v(3, 4);
        Normalize(v);
        EXPECT_NEAR(Magnitude(v), 1.0f, 1e-6f);
        PASS();
    }

    {
        TEST("Normalized");
        vec2 v(3, 4);
        vec2 n = Normalized(v);
        EXPECT_NEAR(Magnitude(n), 1.0f, 1e-6f);
        EXPECT_NEAR(v.x, 3.0f, 1e-6f);
        EXPECT_NEAR(v.y, 4.0f, 1e-6f);
        PASS();
    }

    // --- Distance ---
    {
        TEST("Distance");
        vec2 a(0, 0), b(3, 4);
        EXPECT_NEAR(Distance(a, b), 5.0f, 1e-6f);
        PASS();
    }

    // --- Projection ---
    {
        TEST("Projection");
        vec2 v(3, 4), dir(1, 0);
        vec2 p = Projection(v, dir);
        EXPECT_NEAR(p.x, 3.0f, 1e-6f);
        EXPECT_NEAR(p.y, 0.0f, 1e-6f);
        PASS();
    }

    // --- Perpendicular ---
    {
        TEST("Perpendicular");
        vec2 v(3, 4), dir(1, 0);
        vec2 p = Perpendicular(v, dir);
        EXPECT_NEAR(p.x, 0.0f, 1e-6f);
        EXPECT_NEAR(p.y, 4.0f, 1e-6f);
        PASS();
    }

    // --- Reflection ---
    {
        TEST("Reflection");
        vec2 v(1, -1), normal(0, 1);
        vec2 r = Reflection(v, normal);
        EXPECT_NEAR(r.x, 1.0f, 1e-6f);
        EXPECT_NEAR(r.y, 1.0f, 1e-6f);
        PASS();
    }

    // --- mat2 ---
    {
        TEST("mat2 default constructor");
        mat2 m;
        EXPECT_NEAR(m._11, 1.0f, 1e-6f);
        EXPECT_NEAR(m._22, 1.0f, 1e-6f);
        EXPECT_NEAR(m._12, 0.0f, 1e-6f);
        EXPECT_NEAR(m._21, 0.0f, 1e-6f);
        PASS();
    }

    // --- mat2 Transpose ---
    {
        TEST("mat2 Transpose");
        mat2 m(1, 2, 3, 4);
        mat2 t = Transpose(m);
        EXPECT_NEAR(t._11, 1.0f, 1e-6f);
        EXPECT_NEAR(t._12, 3.0f, 1e-6f);
        EXPECT_NEAR(t._21, 2.0f, 1e-6f);
        EXPECT_NEAR(t._22, 4.0f, 1e-6f);
        PASS();
    }

    // --- mat3 createTranslation ---
    {
        TEST("mat3 createTranslation");
        mat3 m = createTranslation(vec2(5, 10));
        EXPECT_NEAR(m._13, 5.0f, 1e-6f);
        EXPECT_NEAR(m._23, 10.0f, 1e-6f);
        PASS();
    }

    // --- vec3 ---
    {
        TEST("vec3 construction");
        vec3 v(1, 2, 3);
        EXPECT_NEAR(v.x, 1.0f, 1e-6f);
        EXPECT_NEAR(v.y, 2.0f, 1e-6f);
        EXPECT_NEAR(v.z, 3.0f, 1e-6f);
        PASS();
    }
}
