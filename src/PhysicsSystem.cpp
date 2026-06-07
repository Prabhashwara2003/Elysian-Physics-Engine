#include "PhysicsSystem.h"

void PhysicsSystem::AddRigidbody(Rigidbody* body){
	rigidBodies.push_back(body);
}

void PhysicsSystem::Step(float deltaTime) {
	for (Rigidbody* rb : rigidBodies) {
		rb->Integrate(deltaTime);
	}
}
