#include "Renderer.h"

sf::Transform convertToSFMLTransform(mat3& matrix) {

    return sf::Transform(
        matrix[0][0], matrix[0][1], matrix[0][2],
        matrix[1][0], matrix[1][1], matrix[1][2],
        matrix[2][0], matrix[2][1], matrix[2][2]
    );
}

void drawBackground(sf::RenderWindow& window)
{
	sf::RectangleShape shape({ 1750.f, 850.f });
	shape.setFillColor(sf::Color(0, 0, 0));   // Gray
	shape.setPosition({ 25, 25 });
	window.draw(shape);

}

void drawObjects(sf::RenderWindow& window,Circle c) {
	sf::CircleShape shape(2.0f);
	shape.setFillColor(sf::Color(100, 100, 100));
	sf::Transform Transform = convertToSFMLTransform(c.Transform);
	window.draw(shape, Transform);
}


