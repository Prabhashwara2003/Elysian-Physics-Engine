#pragma once
#ifndef _H_PHYSICSSYSTEM
#define _H_PHYSICSSYSTEM
#include <vector>
#include <utility>
#include "Collider2D.h"
#include "Rigidbody.h"
#include "CollisionDetector.h"
#include "CollisionResolver.h"

namespace elysian {

class PhysicsSystem {

protected:
	std::vector<Rigidbody*> rigidBodies;
	std::vector<Collider2D*> colliders;
	CollisionDetector* collisionDetector;
	CollisionResolver* collisionResolver;
	vec2 gravity;

public:

	PhysicsSystem();
	~PhysicsSystem();
	void AddRigidbody(Rigidbody* body);
	void RemoveRigidbody(Rigidbody* body);
	void AddCollider(Collider2D* collider);
	void RemoveCollider(Collider2D* collider);
	void SetGravity(const vec2& g);
	vec2 GetGravity() const;
	void Step(float deltaTime);

private:
	void SyncColliders();
	std::vector<std::pair<Collider2D*, Collider2D*>> BroadPhase();

};

} // namespace elysian

#endif // !_H_PHYSICSSYSTEM

