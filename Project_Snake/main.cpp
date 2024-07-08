#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");
    window.setFramerateLimit(60);

    Snake snake;
    std::vector<Food> foods(15); // Skapa 15 matbitar

    // Timer f�r att s�nka ormens hastighet
    sf::Clock clock;
    sf::Time timeSinceLastMove = sf::Time::Zero;
    sf::Time moveInterval = sf::seconds(0.2f); // Halvera farten genom att �ka intervallet

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Uppdatera timer
        sf::Time deltaTime = clock.restart();
        timeSinceLastMove += deltaTime;

        // Flytta ormen endast om tillr�ckligt med tid har g�tt
        if (timeSinceLastMove >= moveInterval)
        {
            snake.update();
            timeSinceLastMove = sf::Time::Zero;

            // Kontrollera kollision med alla matbitar
            for (auto& food : foods)
            {
                if (snake.getHeadPosition() == food.getPosition())
                {
                    snake.grow();
                    food.spawn();
                }
            }

            if (snake.checkCollision())
            {
                window.close();
            }
        }

        window.clear();
        snake.render(window);

        // Rendera alla matbitar
        for (auto& food : foods)
        {
            food.render(window);
        }

        window.display();
    }

    return 0;
}
