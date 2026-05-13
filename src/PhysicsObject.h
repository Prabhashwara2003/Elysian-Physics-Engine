#pragma once
#include <SFML/Graphics.hpp>
#include "Gravity.h"

class PhysicsObject
{
	

public:
	sf::Vector2f position;
	Gravity gravity;
	sf::Vector2f velocity = sf::Vector2f( 0, 0);

	bool gravityOn;

	PhysicsObject(sf::Vector2f position , bool gravityOn );

	virtual void update(float deltaTime);

	virtual void draw(sf::RenderWindow& window ) = 0;

	virtual ~PhysicsObject() = default;
};

