#pragma once
#include <SFML/Graphics.hpp>
#include "Gravity.h"

class PhysicsObject
{
	

public:
	float xPosition;
	float yPosition;
	Gravity gravity;
	float velocity =0;

	bool gravityOn;

	PhysicsObject(float xPosition , float yPosition , bool gravityOn );

	virtual void update(float deltaTime);

	virtual void draw(sf::RenderWindow& window ) = 0;

	virtual ~PhysicsObject() = default;
};

