#include "Application.h"
#include "Renderer.h"

Application::Application()
	: window(sf::VideoMode({ 1800, 900 }), "Arena")
{
}

void Application::run()
{
	Circle c({ 50.0f,50.0f }, 30.0f, 0.0f);

	sf::Clock clock;
	
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
		drawBackground(window);
		drawObjects(window,c);
		window.display();
	}
}