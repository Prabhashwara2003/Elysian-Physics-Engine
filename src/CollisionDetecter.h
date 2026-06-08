#pragma once
#include "Geometry2D.h"
#include <vector>
#include "Object.h"
#include "shapeTypes.h"
#include "Collider2D.h"

class CollisionDetecter
{
public:
	bool Detect(Collider2D& collider1,Collider2D& collider2);
	bool CircleVsCircle(Circle& c1, Circle& c2);
	bool CircleVsBox(Circle& circle, OrientedRectangle& rectangle);
	bool BoxVsBox(OrientedRectangle& box1, OrientedRectangle& box2);
};

