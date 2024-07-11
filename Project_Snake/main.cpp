#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"
#include "GameState.h"
#include "Menu.h"
#include <vector>

void handleGame(sf::RenderWindow& window, GameState& gameState, Snake& snake, std::vector<Food>& foods, sf::Text& scoreText);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("Fonts/Roboto-Bold.ttf"))
    {
        return -1;
    }

    GameState gameState = MENU;

    Snake snake;
    std::vector<Food> foods(15);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(18);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setPosition(0.f, 0.f);

    Menu menu(font);

    while (window.isOpen())
    {
        switch (gameState)
        {
        case MENU:
            menu.handleMenu(window, gameState);
            break;
        case GAME:
            handleGame(window, gameState, snake, foods, scoreText);
            break;
        case GAME_OVER:
            menu.handleGameOver(window, gameState);
            snake.reset();
            break;
        }
    }

    return 0;
}

void handleGame(sf::RenderWindow& window, GameState& gameState, Snake& snake, std::vector<Food>& foods, sf::Text& scoreText)
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

    std::vector<sf::Vector2f> occupiedPositions;
    occupiedPositions.push_back(snake.getHeadPosition());
    for (std::size_t i = 1; i < snake.getSize(); ++i)
    {
        occupiedPositions.push_back(snake.getBodyPosition(i));
    }

    for (auto& food : foods)
    {
        food.spawn(occupiedPositions);
        occupiedPositions.push_back(food.getPosition());
    }

    sf::Clock clock;
    sf::Time timeSinceLastMove = sf::Time::Zero;
    sf::Time moveInterval = sf::seconds(0.2f);

    while (window.isOpen() && gameState == GAME)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time deltaTime = clock.restart();
        timeSinceLastMove += deltaTime;

        if (timeSinceLastMove >= moveInterval)
        {
            snake.update();
            timeSinceLastMove = sf::Time::Zero;

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
                gameState = GAME_OVER;
            }
        }

        scoreText.setString("Score: " + std::to_string(snake.getscore()));

        window.clear();
        snake.render(window);

        for (auto& food : foods)
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
}
