#pragma once
#include "PhysicsEngine/Export.h"
#include "CollisionInfo.h"

namespace elysian {

class PHYSICSENGINE_API CollisionResolver
{
public:
	CollisionResolver() = default;

	void Resolve(CollisionInfo& info) noexcept;
};

} // namespace elysian
