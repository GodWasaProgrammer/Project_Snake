#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "GameState.h"

class Menu
{
public:
    Menu(sf::Font& font);
    void handleMenu(sf::RenderWindow& window, GameState& gameState);
    void handleGameOver(sf::RenderWindow& window, GameState& gameState);

private:
    sf::Text title;
    sf::Text startMessage;
    sf::Text gameOverText;
    sf::Text restartMessage;
};
#endif // MENU_H