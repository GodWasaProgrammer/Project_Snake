#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"
#include <vector>

int main()
{
    // Skapa fyra ramar runt fönstret
    sf::RectangleShape topBorder(sf::Vector2f(800.f, 20.f)); // Top border
    topBorder.setPosition(0.f, 0.f);
    topBorder.setFillColor(sf::Color::Red);

    sf::RectangleShape bottomBorder(sf::Vector2f(800.f, 20.f)); // Bottom border
    bottomBorder.setPosition(0.f, 580.f);
    bottomBorder.setFillColor(sf::Color::Red);

    sf::RectangleShape leftBorder(sf::Vector2f(20.f, 600.f)); // Left border
    leftBorder.setPosition(0.f, 0.f);
    leftBorder.setFillColor(sf::Color::Red);

    sf::RectangleShape rightBorder(sf::Vector2f(20.f, 600.f)); // Right border
    rightBorder.setPosition(780.f, 0.f);
    rightBorder.setFillColor(sf::Color::Red);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("Fonts/Roboto-Bold.ttf"))
    {
        // Hantera fel
        return -1;
    }

    // Skapa en sf::Text för att visa poängen
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(18);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setPosition(0.f,0.f);

    Snake snake;
    std::vector<Food> foods(15); // Skapa 15 matbitar

    // Skapa en vektor med upptagna positioner (ormens positioner)
    std::vector<sf::Vector2f> occupiedPositions;
    occupiedPositions.push_back(snake.getHeadPosition());
    for (std::size_t i = 1; i < snake.getSize(); ++i)
    {
        occupiedPositions.push_back(snake.getBodyPosition(i));
    }

    // Spawn matbitarna på unika positioner
    for (auto& food : foods)
    {
        food.spawn(occupiedPositions);
        occupiedPositions.push_back(food.getPosition());
    }

    // Timer för att sänka ormens hastighet
    sf::Clock clock;
    sf::Time timeSinceLastMove = sf::Time::Zero;
    sf::Time moveInterval = sf::seconds(0.2f); // Halvera farten genom att öka intervallet

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

        // Flytta ormen endast om tillräckligt med tid har gått
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
                    snake.increaseScore(5);
                    food.spawn(occupiedPositions);
                    occupiedPositions.push_back(food.getPosition());
                }
            }

            if (snake.checkCollision())
            {
                window.close();
            }
        }

        scoreText.setString("Score: " + std::to_string(snake.getscore()));

        window.clear();
        snake.render(window);

        // Rendera alla matbitar
        for (auto& food : foods) // Ändrad från const auto& till auto&
        {
            food.render(window);
        }

        window.draw(topBorder);
        window.draw(bottomBorder);
        window.draw(leftBorder);
        window.draw(rightBorder);
        window.draw(scoreText);

        window.display();
    }

    return 0;
}