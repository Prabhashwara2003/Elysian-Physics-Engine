#include "TestMacros.h"

void suite_TestMath();
void suite_TestGeometry();
void suite_TestCollision();

int main() {
    printf("\n========================================\n");
    printf("  PhysicsEngine Unit Tests\n");
    printf("========================================\n");

    suite_TestMath();
    suite_TestGeometry();
    suite_TestCollision();

    printf("\n========================================\n");
    printf("  Results: %d passed, %d failed out of %d total\n",
           g_testsPassed, g_testsFailed, g_testsPassed + g_testsFailed);
    printf("========================================\n");

    return g_testsFailed > 0 ? 1 : 0;
}
