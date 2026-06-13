# Changelog

## [1.0.0] — 2026-06-09

### Added

- 2D vector math (`vec2`, `vec3`) with dot, cross, normalize, project, reflect
- 2x2, 3x3, 4x4 matrix types with transpose and multiply
- 3x3 transformation matrix builders (translate, rotate, scale)
- 2D geometry primitives: Circle, AABB (`Rectangle2D`), OBB (`OrientedRectangle`), Line
- SAT-based intersection tests: circle-circle, circle-box, box-box, point-in-shape
- Rigidbody dynamics with Euler integration, force/torque accumulation
- Circle and Box colliders with automatic AABB computation
- AABB broad-phase culling (O(n^2))
- Narrow-phase collision detection dispatcher using `dynamic_cast`
- Impulse-based collision resolution with friction (Coulomb) and Baumgarte positional correction
- `PhysicsSystem` orchestrator managing bodies, colliders, detection, and resolution
- CMake build system with install/export support
- Unit test suite with CTest

### Changed

- Headers restructured under `include/` with umbrella `PhysicsEngine/PhysicsEngine.h` header
- DLL export macros (`PHYSICSENGINE_API`) for shared library support
- C++20 constexpr/noexcept annotations on math types
- Drag values now frame-rate independent using `pow(drag, dt * 60)`
- `CollisionInfo` now uses `std::unique_ptr` for leak-safe allocation
- PhysicsSystem uses direct members instead of heap-allocated detector/resolver
- Rigidbody::transform changed from pointer to direct member for ownership safety
- Renamed: `pointInRectangle` → `PointInRectangle`, `getAABB` → `GetAABB`, `RectangleRectangleSaT` → `RectangleRectangleSAT`
- Added `operator+=`, `-=`, `*=`, unary `-`, and left-scalar multiply for `vec2`
- Fixed include guard typo in matrices.h
- All C math functions now use `std::` namespace

### Removed

- Demo application moved to separate repository
