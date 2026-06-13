#include "TestMacros.h"
#include "Geometry2D.h"

using namespace elysian;

void suite_TestGeometry() {
    // --- PointInCircle ---
    {
        TEST("PointInCircle - inside");
        Circle c(vec2(0, 0), 5.0f);
        EXPECT_TRUE(PointInCircle(vec2(3, 0), c));
        PASS();
    }

    {
        TEST("PointInCircle - outside");
        Circle c(vec2(0, 0), 5.0f);
        EXPECT_FALSE(PointInCircle(vec2(6, 0), c));
        PASS();
    }

    {
        TEST("PointInCircle - on edge");
        Circle c(vec2(0, 0), 5.0f);
        EXPECT_FALSE(PointInCircle(vec2(5, 0), c));
        PASS();
    }

    // --- PointInRectangle ---
    {
        TEST("PointInRectangle - inside");
        Rectangle2D rect(vec2(0, 0), vec2(10, 10));
        EXPECT_TRUE(PointInRectangle(vec2(5, 5), rect));
        PASS();
    }

    {
        TEST("PointInRectangle - outside");
        Rectangle2D rect(vec2(0, 0), vec2(10, 10));
        EXPECT_FALSE(PointInRectangle(vec2(15, 5), rect));
        PASS();
    }

    // --- CircleCircle ---
    {
        TEST("CircleCircle - overlapping");
        Circle c1(vec2(0, 0), 5.0f);
        Circle c2(vec2(8, 0), 5.0f);
        EXPECT_TRUE(CircleCircle(c1, c2));
        PASS();
    }

    {
        TEST("CircleCircle - separated");
        Circle c1(vec2(0, 0), 5.0f);
        Circle c2(vec2(20, 0), 5.0f);
        EXPECT_FALSE(CircleCircle(c1, c2));
        PASS();
    }

    // --- CircleRectangle ---
    {
        TEST("CircleRectangle - overlapping");
        Circle c(vec2(5, 5), 5.0f);
        Rectangle2D rect(vec2(0, 0), vec2(10, 10));
        EXPECT_TRUE(CircleRectangle(c, rect));
        PASS();
    }

    {
        TEST("CircleRectangle - separated");
        Circle c(vec2(100, 100), 5.0f);
        Rectangle2D rect(vec2(0, 0), vec2(10, 10));
        EXPECT_FALSE(CircleRectangle(c, rect));
        PASS();
    }

    // --- GetMin / GetMax ---
    {
        TEST("GetMin / GetMax");
        Rectangle2D rect(vec2(5, 5), vec2(10, 20));
        vec2 min = GetMin(rect);
        vec2 max = GetMax(rect);
        EXPECT_NEAR(min.x, 5.0f, 1e-6f);
        EXPECT_NEAR(min.y, 5.0f, 1e-6f);
        EXPECT_NEAR(max.x, 15.0f, 1e-6f);
        EXPECT_NEAR(max.y, 25.0f, 1e-6f);
        PASS();
    }

    // --- RectangleRectangleSAT ---
    {
        TEST("RectangleRectangleSAT - overlapping");
        Rectangle2D a(vec2(0, 0), vec2(10, 10));
        Rectangle2D b(vec2(5, 5), vec2(10, 10));
        EXPECT_TRUE(RectangleRectangleSAT(a, b));
        PASS();
    }

    {
        TEST("RectangleRectangleSAT - separated");
        Rectangle2D a(vec2(0, 0), vec2(10, 10));
        Rectangle2D b(vec2(20, 20), vec2(10, 10));
        EXPECT_FALSE(RectangleRectangleSAT(a, b));
        PASS();
    }

    // --- Line2D ---
    {
        TEST("Line2D Length");
        Line2D line(vec2(0, 0), vec2(3, 4));
        EXPECT_NEAR(Length(line), 5.0f, 1e-6f);
        PASS();
    }

    // --- Interval2D via GetInterval (Rectangle) ---
    {
        TEST("GetInterval for Rectangle2D");
        Rectangle2D rect(vec2(0, 0), vec2(10, 10));
        Interval2D interval = GetInterval(rect, vec2(1, 0));
        EXPECT_NEAR(interval.min, 0.0f, 1e-6f);
        EXPECT_NEAR(interval.max, 10.0f, 1e-6f);
        PASS();
    }

    // --- FromMinMax ---
    {
        TEST("FromMinMax");
        Rectangle2D rect = FromMinMax(vec2(2, 3), vec2(12, 8));
        EXPECT_NEAR(rect.origin.x, 2.0f, 1e-6f);
        EXPECT_NEAR(rect.origin.y, 3.0f, 1e-6f);
        EXPECT_NEAR(rect.size.x, 10.0f, 1e-6f);
        EXPECT_NEAR(rect.size.y, 5.0f, 1e-6f);
        PASS();
    }
}
