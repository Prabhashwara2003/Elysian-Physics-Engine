#include "PhysicsSystem.h"
#include <algorithm>

namespace elysian {

PhysicsSystem::PhysicsSystem()
	: gravity(0.0f, -9.8f) {
	collisionDetector = new CollisionDetector();
	collisionResolver = new CollisionResolver();
}

PhysicsSystem::~PhysicsSystem() {
	delete collisionDetector;
	delete collisionResolver;
}

void PhysicsSystem::AddRigidbody(Rigidbody* body) {
	rigidBodies.push_back(body);
}

void PhysicsSystem::RemoveRigidbody(Rigidbody* body) {
	auto it = std::find(rigidBodies.begin(), rigidBodies.end(), body);
	if (it != rigidBodies.end()) {
		rigidBodies.erase(it);
	}
}

void PhysicsSystem::AddCollider(Collider2D* collider) {
	colliders.push_back(collider);
}

void PhysicsSystem::RemoveCollider(Collider2D* collider) {
	auto it = std::find(colliders.begin(), colliders.end(), collider);
	if (it != colliders.end()) {
		colliders.erase(it);
	}
}

void PhysicsSystem::SetGravity(const vec2& g) {
	gravity = g;
}

vec2 PhysicsSystem::GetGravity() const {
	return gravity;
}

void PhysicsSystem::Step(float deltaTime) {
	for (Rigidbody* rb : rigidBodies) {
		if (rb->isGravityOn) {
			rb->ApplyGravity(gravity);
		}
		rb->Integrate(deltaTime);
	}

	SyncColliders();

	std::vector<std::pair<Collider2D*, Collider2D*>> pairs = BroadPhase();

	for (auto& [a, b] : pairs) {
		CollisionInfo* info = collisionDetector->Detect(a, b);
		if (info && info->hasCollision) {
			collisionResolver->Resolve(*info);
		}
		delete info;
	}
}

void PhysicsSystem::SyncColliders() {
	for (Collider2D* c : colliders) {
		c->SyncTransform();
	}
}

std::vector<std::pair<Collider2D*, Collider2D*>> PhysicsSystem::BroadPhase() {
	std::vector<std::pair<Collider2D*, Collider2D*>> pairs;

	for (size_t i = 0; i < colliders.size(); i++) {
		for (size_t j = i + 1; j < colliders.size(); j++) {
			if (RectangleRectangleSaT(colliders[i]->getAABB(), colliders[j]->getAABB())) {
				pairs.push_back({ colliders[i], colliders[j] });
			}
		}
	}
	return pairs;
}

} // namespace elysian
