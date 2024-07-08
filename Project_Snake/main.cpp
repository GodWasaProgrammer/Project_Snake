#include <SFML/Graphics.hpp>
#include "Snake.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");

	window.setFramerateLimit(60);

	Snake snake;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		snake.update();

		// collision check
		if (snake.checkCollision())
		{
			window.close();
		}

		// clear window
		window.clear();
		snake.render(window);
		window.display();

		// game logic


		// window display
		window.display();
	}

	return 0;
}