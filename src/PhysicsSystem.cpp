#include "PhysicsSystem.h"

void PhysicsSystem::Update(float deltaTime) {
	for (int i = 0, size = objects.size(); i < size; i++) {
		objects[i]->ApplyForce();
	}
	for (int i = 0, size = objects.size(); i < size; i++) {
		bodies[i]->Update(deltaTime);
	}
	
}