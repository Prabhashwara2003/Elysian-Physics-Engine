#include "Rectangle.h"

Rectangle::Rectangle(sf::Vector2f position, float height, float width, sf::Color color, bool gravityOn)
	:PhysicsObject(position, gravityOn), height(height), width(width), color(color)
{

}

void Rectangle::draw(sf::RenderWindow& window)
{
	sf::RectangleShape shape({ width , height });
	shape.setFillColor(color);
	shape.setPosition(position);
	window.draw(shape);
}

void Rectangle::update(float deltaTime)
{
	if (gravityOn)
	{
		velocity = gravity.applyGravity(position.y, deltaTime, velocity);
		position.y += velocity.y * deltaTime * 100;
		position.x += velocity.x * deltaTime * 100;
	}
	midpoint = { position.x + width / 2.f , position.y + height / 2.f };
}