#pragma once
#ifndef _H_PHYSICSSYSTEM
#define _H_PHYSICSSYSTEM

#include "PhysicsEngine/Export.h"
#include <vector>
#include <utility>
#include "Collider2D.h"
#include "Rigidbody.h"
#include "CollisionDetector.h"
#include "CollisionResolver.h"

namespace elysian {

class PHYSICSENGINE_API PhysicsSystem {

protected:
	std::vector<Rigidbody*> rigidBodies;
	std::vector<Collider2D*> colliders;
	CollisionDetector collisionDetector;
	CollisionResolver collisionResolver;
	vec2 gravity;

public:
	PhysicsSystem() noexcept;
	~PhysicsSystem() = default;

	PhysicsSystem(const PhysicsSystem&) = delete;
	PhysicsSystem& operator=(const PhysicsSystem&) = delete;

	void AddRigidbody(Rigidbody* body) noexcept;
	void RemoveRigidbody(Rigidbody* body) noexcept;
	void AddCollider(Collider2D* collider) noexcept;
	void RemoveCollider(Collider2D* collider) noexcept;
	void SetGravity(const vec2& g) noexcept;
	vec2 GetGravity() const noexcept;
	void Step(float deltaTime) noexcept;

private:
	void SyncColliders() noexcept;
	std::vector<std::pair<Collider2D*, Collider2D*>> BroadPhase() noexcept;
};

} // namespace elysian

#endif // !_H_PHYSICSSYSTEM
