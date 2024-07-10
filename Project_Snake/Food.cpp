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
    // Anta att varje cell i spelet är 20x20 pixlar och ramen är också 20 pixlar bred
    int cellSize = 20;
    int borderWidth = 20;

    int maxX = (800 - 2 * borderWidth) / cellSize; // Justera för ramen
    int maxY = (600 - 2 * borderWidth) / cellSize; // Justera för ramen

    sf::Vector2f newPosition;
    do
    {
        int x = std::rand() % maxX;
        int y = std::rand() % maxY;
        newPosition = sf::Vector2f((x * cellSize) + borderWidth, (y * cellSize) + borderWidth); // Justera positionen för att undvika ramen
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

