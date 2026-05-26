#pragma once
#include <SFML/Graphics.hpp>
#include "Gravity.h"
#include "vectors.h"

class PhysicsObject
{
	

public:
	vec2 position;
	Gravity gravity;
	vec2 velocity = { 0, 0 };

	bool gravityOn;

	PhysicsObject(vec2 position , bool gravityOn );

	virtual void update(float deltaTime);

	virtual void draw(sf::RenderWindow& window ) = 0;

	virtual ~PhysicsObject() = default;
};

