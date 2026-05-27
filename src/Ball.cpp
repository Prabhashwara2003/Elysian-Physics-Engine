#include "Ball.h"
/*
Ball::Ball(sf::Vector2f position, float radius, sf::Color color, bool gravityOn)
	:PhysicsObject(position ,gravityOn), radius(radius), color(color)
{	
	
}

void Ball::draw(sf::RenderWindow& window )
{
	sf::CircleShape shape(radius);
	shape.setFillColor(color);
	shape.setPosition(position);
	shape.setPointCount(100);
	window.draw(shape);
}

void Ball::update(float deltaTime) {
	if (gravityOn)
	{
		velocity = gravity.applyGravity(position.y, deltaTime, velocity);

	}
	position.y += velocity.y * deltaTime * 100;
	position.x += velocity.x * deltaTime * 100;
	midpoint = { position.x + radius , position.y + radius };
}*/