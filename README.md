# Elysian Physics Engine

A 2D rigidbody physics engine with collision detection and resolution, written in C++20.

## Features

- **Rigidbody dynamics** — Euler integration, force/torque accumulation, impulse-based velocity changes
- **Collision primitives** — Circle, Axis-Aligned Bounding Box (AABB), Oriented Bounding Box (OBB)
- **Collision detection** — Broad-phase AABB overlap culling + narrow-phase SAT (Separating Axis Theorem) for circle-circle, circle-box, and box-box
- **Collision resolution** — Normal impulse, friction impulse (Coulomb), positional correction (Baumgarte stabilization)
- **Vector/matrix math** — `vec2`, `mat2`/`mat3`/`mat4` with common linear algebra operations
- **2D geometry utilities** — Point-in-shape tests, line intersections, interval projections
- **Namespace** — All types under `elysian::`

## Dependencies

- **C++20** compiler (MSVC 2022+, GCC 11+, Clang 14+)
- No external dependencies

## Building

```bash
git clone <repo-url>
cd PhysicsEngine
cmake -B build
cmake --build build
```

Run tests:

```bash
ctest --test-dir build
```

## Quick Start

```cpp
#include "PhysicsEngine/PhysicsEngine.h"

using namespace elysian;

PhysicsSystem physics;
physics.SetGravity(vec2(0.0f, 9.8f));

// Create a static ground body
Rigidbody ground(vec2(400, 590), 0.0f, vec2(1, 1));
ground.mass = 0.0f;
ground.inverseMass = 0.0f;
ground.isGravityOn = false;

OrientedRectangle groundRect(vec2(400, 590), vec2(400, 20), 0.0f);
BoxCollider groundCollider(&groundRect, &ground.transform);
groundCollider.rigidbody = &ground;

physics.AddRigidbody(&ground);
physics.AddCollider(&groundCollider);

// Create a falling circle
Rigidbody ball(vec2(400, 100), 0.0f, vec2(1, 1));
ball.bounciness = 0.5f;

Circle ballCircle(vec2(400, 100), 25.0f);
CircleCollider ballCollider(&ballCircle, &ball.transform);
ballCollider.rigidbody = &ball;

physics.AddRigidbody(&ball);
physics.AddCollider(&ballCollider);

// Advance simulation
physics.Step(1.0f / 60.0f);
```

## API Overview

All types live in the `elysian` namespace.

### Math (`vectors.h`, `matrices.h`)

| Type | Description |
|------|-------------|
| `vec2` | 2D vector — dot, cross, normalize, project, reflect |
| `vec3` | 3D vector (placeholder) |
| `mat2` / `mat3` / `mat4` | Matrix types with transpose and multiply |
| free functions | `Dot`, `Cross`, `Magnitude`, `Normalize`, `Angle`, `Projection`, `Reflection`, etc. |

### Geometry (`Geometry2D.h`)

| Type | Description |
|------|-------------|
| `Point2D` | Alias for `vec2` |
| `Line2D` | Line segment defined by Start/End |
| `Circle` | Circle with Position and radius |
| `Rectangle2D` | Axis-aligned rect with origin and size |
| `OrientedRectangle` | OBB with position, halfExtents, rotation |
| `Interval2D` | 1D interval (min/max) for SAT |

Intersection tests: `PointInCircle`, `PointInRectangle`, `CircleCircle`, `CircleRectangle`, `RectangleRectangleSAT`, and oriented variants.

### Rigidbody (`Rigidbody.h`)

| Method | Description |
|--------|-------------|
| `Integrate(dt)` | Euler integration step |
| `ApplyForce(force)` | Accumulate force |
| `ApplyImpulse(impulse)` | Instantaneous velocity change |
| `ApplyImpulseAtPosition(impulse, point, moi)` | Impulse with angular component |
| `ApplyForceAtPosition(force, point)` | Force with torque |
| `ApplyTorque(torque)` | Accumulate torque |
| `ApplyGravity(gravity)` | Add gravitational force |

### Collider (`Collider2D.h`)

| Type | Description |
|------|-------------|
| `Collider2D` | Abstract base class |
| `CircleCollider` | Circle collider — wraps a `Circle*` |
| `BoxCollider` | Box collider — wraps an `OrientedRectangle*` |

### Collision Detection (`CollisionDetector.h`)

| Method | Description |
|--------|-------------|
| `Detect(a, b)` | Dispatcher — routes to the correct narrow-phase |
| `CircleVsCircle(a, b)` | Circle-circle narrow phase |
| `CircleVsBox(circle, box)` | Circle-box narrow phase |
| `BoxVsBox(a, b)` | OBB-OBB SAT narrow phase |

### Collision Resolution (`CollisionResolver.h`)

| Method | Description |
|--------|-------------|
| `Resolve(info)` | Applies normal impulse + friction + positional correction |

### Physics System (`PhysicsSystem.h`)

| Method | Description |
|--------|-------------|
| `AddRigidbody(body)` | Register a rigidbody |
| `RemoveRigidbody(body)` | Unregister |
| `AddCollider(collider)` | Register a collider |
| `RemoveCollider(collider)` | Unregister |
| `SetGravity(g)` / `GetGravity()` | Gravity vector accessor |
| `Step(dt)` | Advance one frame: gravity → integrate → sync → broad-phase → narrow-phase → resolve |

## File Structure

```
include/
├── PhysicsEngine/
│   ├── PhysicsEngine.h     — Single include header
│   ├── Export.h            — DLL export/import macros
│   └── Version.h           — Version macros
├── vectors.h / .cpp           — 2D/3D vector math
├── matrices.h / .cpp          — 2x2, 3x3, 4x4 matrix math
├── Geometry2D.h / .cpp        — 2D shapes and intersection tests
├── ShapeTypes.h               — Shape enum (circle, box)
├── Transform.h / .cpp         — Position, rotation, scale
├── Rigidbody.h / .cpp         — Rigidbody dynamics
├── Collider2D.h / .cpp        — Collider base and derived types
├── CollisionInfo.h / .cpp     — Collision data carrier
├── CollisionDetector.h / .cpp — Collision detection
├── CollisionResolver.h / .cpp — Impulse-based resolution
└── PhysicsSystem.h / .cpp     — System orchestrator
```

## Demo Application

A separate demo application with SFML rendering is available at:
**[Elysian Physics Demo](https://github.com/your-username/elysian-physics-demo)** (placeholder — link to your demo repo)

## License

Distributed under the MIT License. See [LICENSE](LICENSE).
