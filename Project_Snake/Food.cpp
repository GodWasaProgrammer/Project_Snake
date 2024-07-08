#include "Food.h"
#include <cstdlib>
#include <ctime>

Food::Food()
{
    std::string imagePath = "img/apple.png";

    if (!texture.loadFromFile(imagePath))
    {
        throw std::runtime_error("Failed to load food texture from: " + imagePath);
    }

    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f); 

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
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

    sprite.setPosition(newPosition);
}

void Food::render(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

sf::Vector2f Food::getPosition() const
{
    return sprite.getPosition();
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

