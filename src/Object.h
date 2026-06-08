#pragma once
#include "Transform.h"
#include "ShapeTypes.h"

namespace elysian {

class Object
{
public:
	Transform transform;
	Shape shape;

	Object();
};

} // namespace elysian

