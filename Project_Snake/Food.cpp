#include "Food.h"
#include <cstdlib>
#include <ctime>

Food::Food()
{
    food.setSize(sf::Vector2f(20.f, 20.f));
    food.setFillColor(sf::Color::Red);
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Initiera slumpgeneratorn
    spawn();
}

void Food::spawn()
{
    int maxX = 800 / 20;
    int maxY = 600 / 20;
    int x = std::rand() % maxX;
    int y = std::rand() % maxY;
    food.setPosition(x * 20.f, y * 20.f);
}

void Food::render(sf::RenderWindow& window) const
{
    window.draw(food);
}

sf::Vector2f Food::getPosition() const
{
    return food.getPosition();
}