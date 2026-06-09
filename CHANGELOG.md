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
- AABB broad-phase culling (O(n²))
- Narrow-phase collision detection dispatcher using `dynamic_cast`
- Impulse-based collision resolution with friction (Coulomb) and Baumgarte positional correction
- `PhysicsSystem` orchestrator managing bodies, colliders, detection, and resolution
- CMake build system with SFML 3 dependency
- Demo application with SFML rendering
