#pragma once
#include "CollisionInfo.h"

namespace elysian {

class CollisionResolver
{
public:
	CollisionResolver();
	void Resolve(CollisionInfo& info);

};

} // namespace elysian

