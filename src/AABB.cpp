#include "AABB.h"

AABB::AABB(vec2 min, vec2 max) 
	: aabbRect(FromMinMax(min, max))
{}