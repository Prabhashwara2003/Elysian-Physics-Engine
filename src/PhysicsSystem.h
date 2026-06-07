#pragma once
#ifndef _H_PHYSICSSYSTEM
#define _H_PHYSICSSYSTEM

#include "Rigidbody.h"
#include "Transform.h"
#include "Object.h"

class PhysicsSystem {

protected:
	std::vector<Object*> objects;
	std::vector<Rigidbody* > rigidBodies;

public:

	void AddRigidbody(Rigidbody* body);
	void Step(float deltaTime);

};


#endif // !_H_PHYSICSSYSTEM

