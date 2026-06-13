#include "PhysicsSystem.h"
#include <algorithm>

namespace elysian {

	PhysicsSystem::PhysicsSystem() noexcept
		: gravity(0.0f, 980.0f)
	{
	}

	void PhysicsSystem::AddRigidbody(Rigidbody* body) noexcept {
		rigidBodies.push_back(body);
	}

	void PhysicsSystem::RemoveRigidbody(Rigidbody* body) noexcept {
		auto it = std::find(rigidBodies.begin(), rigidBodies.end(), body);
		if (it != rigidBodies.end())
			rigidBodies.erase(it);
	}

	void PhysicsSystem::AddCollider(Collider2D* collider) noexcept {
		colliders.push_back(collider);
	}

	void PhysicsSystem::RemoveCollider(Collider2D* collider) noexcept {
		auto it = std::find(colliders.begin(), colliders.end(), collider);
		if (it != colliders.end())
			colliders.erase(it);
	}

	void PhysicsSystem::SetGravity(const vec2& g) noexcept {
		gravity = g;
	}

	vec2 PhysicsSystem::GetGravity() const noexcept {
		return gravity;
	}

	void PhysicsSystem::Step(float deltaTime) noexcept {
		for (Rigidbody* rb : rigidBodies) {
			if (rb->isGravityOn)
				rb->ApplyGravity(gravity);
			rb->Integrate(deltaTime);
		}

		SyncColliders();

		auto pairs = BroadPhase();

		const int SOLVER_ITERATIONS = 5;
		for (int iter = 0; iter < SOLVER_ITERATIONS; iter++) {
			SyncColliders();

			for (auto& [a, b] : pairs) {
				auto info = collisionDetector.Detect(a, b);
				if (info && info->hasCollision) {
					collisionResolver.Resolve(*info);
				}
			}
		}
	}

	void PhysicsSystem::SyncColliders() noexcept {
		for (Collider2D* c : colliders)
			c->SyncTransform();
	}

	std::vector<std::pair<Collider2D*, Collider2D*>> PhysicsSystem::BroadPhase() noexcept {
		std::vector<std::pair<Collider2D*, Collider2D*>> pairs;
		for (size_t i = 0; i < colliders.size(); i++) {
			for (size_t j = i + 1; j < colliders.size(); j++) {
				if (!colliders[i]->rigidbody->inverseMass &&
					!colliders[j]->rigidbody->inverseMass)
					continue;

				if (RectangleRectangleSAT(colliders[i]->GetAABB(), colliders[j]->GetAABB())) {
					pairs.push_back({ colliders[i], colliders[j] });
				}
			}
		}
		return pairs;
	}

} // namespace elysian
