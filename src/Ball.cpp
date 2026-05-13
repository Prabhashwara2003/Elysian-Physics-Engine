#include "Ball.h"

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
		if (position.y >= 825)
		{
			position.y = 825;
			velocity.y = -velocity.y * .8f;
		}
		if (position.x >= 1725)
		{
			position.x = 1725;
			velocity.x = -velocity.x * .8f;
		}
		if (position.x <= 25)
		{
			position.x = 25;
			velocity.x = -velocity.x * .8f;
		}
		//position.y += velocity.y * deltaTime * 100;
		//position.x += velocity.x * deltaTime * 100;
	}
	position.y += velocity.y * deltaTime * 100;
	position.x += velocity.x * deltaTime * 100;
	midpoint = { position.x + radius , position.y + radius };
}