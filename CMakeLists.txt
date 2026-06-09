cmake_minimum_required(VERSION 3.14)
project(PhysicsEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_library(PhysicsEngine
    src/Collider2D.cpp
    src/CollisionDetector.cpp
    src/CollisionInfo.cpp
    src/CollisionResolver.cpp
    src/Geometry2D.cpp
    src/matrices.cpp
    src/PhysicsSystem.cpp
    src/Rigidbody.cpp
    src/Transform.cpp
    src/vectors.cpp
)

target_include_directories(PhysicsEngine PUBLIC src)
target_link_libraries(PhysicsEngine PUBLIC SFML::Graphics SFML::Window SFML::System)

add_executable(Demo demo/main.cpp)
target_link_libraries(Demo PRIVATE PhysicsEngine)
