#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>
#include <vector>

class Food
{
public:
    Food();
    void spawn(const std::vector<sf::Vector2f>& occupiedPositions);
    void render(sf::RenderWindow& window) const;
    sf::Vector2f getPosition() const;

private:
    sf::RectangleShape food;
    bool isPositionOccupied(const sf::Vector2f& position, const std::vector<sf::Vector2f>& occupiedPositions) const;
};

#endif // FOOD_H
