#pragma once
#include "PhysicsObject.h"
class Rectangle : public PhysicsObject
	 
{

public:
	sf::Vector2f midpoint;
	sf::Color color;
	float height;
	float width;

	Rectangle(sf::Vector2f position, float height, float width, sf::Color color, bool gravityOn);

	void draw(sf::RenderWindow& window);

	void update(float deltaTime) override;
};

