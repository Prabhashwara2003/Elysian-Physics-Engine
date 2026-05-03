#include "Ball.h"

Ball::Ball(float xPosition, float yPosition, float radius, sf::Color color, bool gravityOn)
	:PhysicsObject(xPosition, yPosition ,gravityOn), radius(radius), color(color)
{	
	
}

void Ball::draw(sf::RenderWindow& window )
{
	sf::CircleShape shape(radius);
	shape.setFillColor(color);
	shape.setPosition({ xPosition , yPosition});
	window.draw(shape);
}

void Ball::update(float deltaTime) {
	if (gravityOn)
	{
		velocity = gravity.applyGravity(yPosition, deltaTime, velocity);
		if (yPosition >= 825)
		{
			yPosition = 825;
			velocity = -velocity * .8f;
		}
		yPosition += velocity * deltaTime * 100;
	}

	midpoint = { xPosition + radius , yPosition + radius };
}