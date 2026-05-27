#pragma once
#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "matrices.h";

	
//void drawCircle( float deltaTime);
sf::Transform convertToSFMLTransform(const mat3& matrix);
void drawBackground(sf::RenderWindow& window);
void drawObjects(sf::RenderWindow& window,Circle c);

	
