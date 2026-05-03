#pragma once
#include "PhysicsObject.h"
#include <SFML/Graphics.hpp>

class Ball : public PhysicsObject
{

public:
    float radius;
    sf::Color color;
    sf::Vector2f midpoint;
    Ball(float xPosition, float yPosition, float radius, sf::Color color, bool gravityOn);
    void draw(sf::RenderWindow& window );
    void update(float deltaTime) override;
};

