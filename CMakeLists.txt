cmake_minimum_required(VERSION 3.14)
project(PhysicsEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate version header
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/PhysicsEngine/Version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/include/PhysicsEngine/Version.h
)

add_library(${PROJECT_NAME}
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

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated/include>
        $<INSTALL_INTERFACE:include>
)

option(PHYSICSENGINE_SHARED "Build PhysicsEngine as shared library" OFF)

if(PHYSICSENGINE_SHARED)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
            PHYSICSENGINE_EXPORTS
    )
else()
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
            PHYSICSENGINE_STATIC
    )
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/generated/include/PhysicsEngine/Version.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/PhysicsEngine
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Tests
option(PHYSICSENGINE_BUILD_TESTS "Build physics engine tests" ON)

if(PHYSICSENGINE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
