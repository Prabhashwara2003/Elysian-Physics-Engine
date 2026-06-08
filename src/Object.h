#pragma once
#include <SFML/Graphics.hpp>
#include "Transform.h"
#include <iostream>

enum class Shape {
	circle,
	box
};

class Object
{
public:
	Transform transform;
	Shape shape;

	Object();
};

