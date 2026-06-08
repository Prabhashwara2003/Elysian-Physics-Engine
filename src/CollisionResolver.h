#pragma once
#include "CollisionInfo.h"

class CollisionResolver
{
public:
	CollisionInfo& info;
	CollisionResolver();
	void Resolve(CollisionInfo& info);

};

