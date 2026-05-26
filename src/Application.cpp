#include "Application.h"
#include "Renderer.h"
#include "PhysicsObject.h"
#include "Ball.h"
#include "Rectangle.h"
#include "Collision.h"

Application::Application()
	: window(sf::VideoMode({ 1800, 900 }), "Arena")
{
}

void Application::run()
{
	std::vector<PhysicsObject* > physicsObjects;
	
	physicsObjects.push_back(new Rectangle({0, 875}, 25.f, 1800.f, sf::Color(128, 128, 128),false));
	physicsObjects.push_back(new Rectangle({0, 0}, 900.f, 25.f, sf::Color(128, 128, 128), false));
	physicsObjects.push_back(new Rectangle({0, 0}, 25.f, 1800.f, sf::Color(128, 128, 128), false));
	physicsObjects.push_back(new Rectangle({1775, 0}, 900.f, 25.f, sf::Color(128, 128, 128), false));
	physicsObjects.push_back(new Rectangle({ 550, 600 }, 100.f, 100.f, sf::Color(255, 180, 100), false));
	physicsObjects.push_back(new Ball({ 200, 225 }, 25.f, sf::Color(140, 220, 140), true));
	physicsObjects.push_back(new Ball({500, 300}, 25.f, sf::Color(0, 0, 100), true));
	physicsObjects.push_back(new Ball({1100, 250}, 25.f, sf::Color(100, 100, 100), true));
	physicsObjects.push_back(new Ball({ 100, 250 }, 25.f, sf::Color(100, 100, 100), true));
	physicsObjects.push_back(new Ball({ 900, 250 }, 25.f, sf::Color(100, 100, 100), true));
	physicsObjects.push_back(new Ball({ 800, 250 }, 25.f, sf::Color(100, 100, 100), true));
	physicsObjects.push_back(new Ball({ 600, 250 }, 25.f, sf::Color(100, 100, 100), true));
	physicsObjects.push_back(new Ball({ 700, 250 }, 25.f, sf::Color(100, 100, 100), true));
	
	std::vector<Ball*> balls;
	std::vector<Rectangle*> rectangles;

	for (auto* obj : physicsObjects)
	{
		Ball* ball = dynamic_cast<Ball*>(obj);
		if (ball != nullptr)
		{
			balls.push_back(ball);
		}
		Rectangle* rectangle = dynamic_cast<Rectangle*>(obj);
		if (rectangle != nullptr)
		{
			rectangles.push_back(rectangle);
		}
	}

	sf::Clock clock;

	Renderer render(window);

	Collision collision;

	window.setPosition({ 10, 50 });

	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		while (const std::optional<sf::Event> event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			{
				window.close();
			}

		}
		window.clear();
		
		//render background
		render.drawBackground();

		for (PhysicsObject* physicsObject : physicsObjects)
		{
			physicsObject->update(deltaTime);
		}

		for (Ball* ball : balls)
		{
			ball->update(deltaTime);
		}

		for (Rectangle* rectangle : rectangles)
		{
			rectangle->update(deltaTime);
		}

		collision.checkBallRect(balls, rectangles);

		collision.checkCollision(balls);

		for (auto* physicsObject : physicsObjects)
		{
			render.renderPhysicsObject(*physicsObject);
		}

		window.display();
	}
}