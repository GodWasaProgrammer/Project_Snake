#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <deque>
#include <map>

class Snake
{
public:
    enum Direction { None, Up, Down, Left, Right };

    Snake();

    void move();
    void grow();
    void update();
    void render(sf::RenderWindow& window);
    bool checkCollision();
    int getscore() const;
    void increaseScore(int amount);
    sf::Vector2f getHeadPosition() const;
    sf::Vector2f getBodyPosition(std::size_t index) const;
    std::size_t getSize() const;
    void setDirection(Direction dir);
    Direction getDirection() const;

private:
    Direction direction;
    std::deque<sf::RectangleShape> body;
    sf::Vector2f directionVector;
    std::map<sf::Keyboard::Key, bool> keyStatus; // För att hålla reda på statusen för varje tangent
    sf::RectangleShape createSegment(float x, float y);
    void updateDirection();
    int score;

};

#endif // SNAKE_H
