#pragma once
#include <cstdio>
#include <cmath>

static int g_testsPassed = 0;
static int g_testsFailed = 0;

#define TEST(name) \
    do { \
        printf("  TEST: %s ... ", name); \
        fflush(stdout); \
    } while(0)

#define PASS() \
    do { \
        printf("PASSED\n"); \
        g_testsPassed++; \
    } while(0)

#define FAIL(msg) \
    do { \
        printf("FAILED (%s)\n", msg); \
        g_testsFailed++; \
    } while(0)

#define EXPECT_TRUE(expr) \
    do { \
        if (!(expr)) { \
            FAIL(#expr); \
            return; \
        } \
    } while(0)

#define EXPECT_FALSE(expr) \
    do { \
        if ((expr)) { \
            FAIL("!" #expr); \
            return; \
        } \
    } while(0)

#define EXPECT_EQ(a, b) \
    do { \
        if ((a) != (b)) { \
            FAIL("expected equality"); \
            return; \
        } \
    } while(0)

#define EXPECT_NEAR(a, b, eps) \
    do { \
        if (std::abs((a) - (b)) > (eps)) { \
            FAIL("expected near"); \
            return; \
        } \
    } while(0)
