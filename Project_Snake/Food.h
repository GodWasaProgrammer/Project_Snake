#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>

class Food
{
public:
    Food();
    void spawn();
    void render(sf::RenderWindow& window) const;
    sf::Vector2f getPosition() const;

private:
    sf::RectangleShape food;
};

#endif // !FOOD_H
