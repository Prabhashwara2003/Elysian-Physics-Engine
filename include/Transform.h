#pragma once

#include "PhysicsEngine/Export.h"
#include "vectors.h"

namespace elysian {

class PHYSICSENGINE_API Transform
{
public:
	vec2 position;
	float rotation;
	vec2 scale;

	constexpr Transform(vec2 position, float rotation, vec2 scale) noexcept
		: position(position), rotation(rotation), scale(scale) {}

	void Translate(vec2 delta) noexcept;
	void Rotate(float angle) noexcept;
};

} // namespace elysian
