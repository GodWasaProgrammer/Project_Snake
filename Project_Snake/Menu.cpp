#include "Menu.h"

Menu::Menu(sf::Font& font)
{
    title.setFont(font);
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setString("Snake Game");
    title.setPosition(250.f, 200.f);

    startMessage.setFont(font);
    startMessage.setCharacterSize(20);
    startMessage.setFillColor(sf::Color::White);
    startMessage.setString("Press Enter to Start");
    startMessage.setPosition(300.f, 300.f);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over");
    gameOverText.setPosition(300.f, 150.f);

    restartMessage.setFont(font);
    restartMessage.setCharacterSize(20);
    restartMessage.setFillColor(sf::Color::White);
    restartMessage.setString("Press Enter to Restart");
    restartMessage.setPosition(300.f, 300.f);
}

void Menu::handleMenu(sf::RenderWindow& window, GameState& gameState)
{
    while (window.isOpen() && gameState == MENU)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                gameState = GAME;
        }

        window.clear();
        window.draw(title);
        window.draw(startMessage);
        window.display();
    }
}

void Menu::handleGameOver(sf::RenderWindow& window, GameState& gameState)
{
    while (window.isOpen() && gameState == GAME_OVER)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                gameState = MENU;
        }

        window.clear();
        window.draw(gameOverText);
        window.draw(restartMessage);
        window.display();
    }
}
