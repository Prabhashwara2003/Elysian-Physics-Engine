#pragma once
#ifndef _H_PHYSICSSYSTEM
#define _H_PHYSICSSYSTEM

#include "Rigidbody.h"
#include "Transform.h"
#include "Object.h"

class PhysicsSystem {

protected:
	std::vector<Object*> objects;

public:
	void Update(float deltaTime);
	void Render();
	void AddRigidbody(Rigidbody* body);
	void ClearRigidbody();

};


#endif // !_H_PHYSICSSYSTEM

