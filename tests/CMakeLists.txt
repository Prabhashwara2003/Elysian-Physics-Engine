# PhysicsEngine unit tests
add_executable(PhysicsEngineTests
    main.cpp
    TestMath.cpp
    TestGeometry.cpp
    TestCollision.cpp
)

target_link_libraries(PhysicsEngineTests PRIVATE PhysicsEngine::PhysicsEngine)

add_test(NAME PhysicsEngineTests COMMAND PhysicsEngineTests)
