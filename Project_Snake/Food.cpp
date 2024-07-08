#include "Food.h"
#include <cstdlib>
#include <ctime>

Food::Food()
{
    food.setSize(sf::Vector2f(20.f, 20.f));
    food.setFillColor(sf::Color::Red);
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Initiera slumpgeneratorn
}

void Food::spawn(const std::vector<sf::Vector2f>& occupiedPositions)
{
    int maxX = 800 / 20;
    int maxY = 600 / 20;

    sf::Vector2f newPosition;
    do
    {
        int x = std::rand() % maxX;
        int y = std::rand() % maxY;
        newPosition = sf::Vector2f(x * 20.f, y * 20.f);
    } while (isPositionOccupied(newPosition, occupiedPositions));

    food.setPosition(newPosition);
}

bool Food::isPositionOccupied(const sf::Vector2f& position, const std::vector<sf::Vector2f>& occupiedPositions) const
{
    for (const auto& occupiedPosition : occupiedPositions)
    {
        if (position == occupiedPosition)
        {
            return true;
        }
    }
    return false;
}

void Food::render(sf::RenderWindow& window) const
{
    window.draw(food);
}

sf::Vector2f Food::getPosition() const
{
    return food.getPosition();
}
