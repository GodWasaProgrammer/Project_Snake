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
    sf::Sprite sprite; //changed rectshape to sprite
    sf::Texture texture; // to hold the picture
    sf::Vector2f position;

    bool isPositionOccupied(const sf::Vector2f& position, const std::vector<sf::Vector2f>& occupiedPositions) const;
};

#endif // FOOD_H
