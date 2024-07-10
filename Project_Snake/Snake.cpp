#include "Snake.h"

Snake::Snake() : direction(Direction::Right)
{
    // Initial position for the snake
    body.push_back(createSegment(100.f, 100.f));
    body.push_back(createSegment(80.f, 100.f));
    body.push_back(createSegment(60.f, 100.f));
    directionVector = sf::Vector2f(20.f, 0.f); // Rörelsevektor
}

sf::RectangleShape Snake::createSegment(float x, float y)
{
    sf::RectangleShape segment(sf::Vector2f(20.f, 20.f));
    segment.setFillColor(sf::Color::Green);
    segment.setPosition(x, y);
    return segment;
}

void Snake::move()
{
    for (int i = body.size() - 1; i > 0; --i)
    {
        body[i].setPosition(body[i - 1].getPosition());
    }
    body[0].move(directionVector);
}

void Snake::grow()
{
    sf::Vector2f newSegmentPosition = body.back().getPosition();
    body.push_back(createSegment(newSegmentPosition.x, newSegmentPosition.y));
}

void Snake::update()
{
    updateDirection();
    move();
}

void Snake::render(sf::RenderWindow& window)
{
    for (const auto& segment : body)
    {
        window.draw(segment);
    }
}

bool Snake::checkCollision()
{
    sf::Vector2f headPosition = body[0].getPosition();

    // Kollision med väggarna
    if (headPosition.x < 20.f || headPosition.x >= 780.f || headPosition.y < 20.f || headPosition.y >= 580.f)
    {
        return true;
    }

    // Kollision med kroppen
    for (size_t i = 1; i < body.size(); ++i)
    {
        if (body[i].getPosition() == headPosition)
        {
            return true;
        }
    }

    return false;
}

void Snake::updateDirection()
{
    // Uppdatera statusen för varje tangent
    keyStatus[sf::Keyboard::Up] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    keyStatus[sf::Keyboard::Down] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    keyStatus[sf::Keyboard::Left] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    keyStatus[sf::Keyboard::Right] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

    // Hantera riktning baserat på tangentstatus
    if (keyStatus[sf::Keyboard::Up] && direction != Direction::Down)
    {
        direction = Direction::Up;
        directionVector = sf::Vector2f(0.f, -20.f);
    }
    else if (keyStatus[sf::Keyboard::Down] && direction != Direction::Up)
    {
        direction = Direction::Down;
        directionVector = sf::Vector2f(0.f, 20.f);
    }
    else if (keyStatus[sf::Keyboard::Left] && direction != Direction::Right)
    {
        direction = Direction::Left;
        directionVector = sf::Vector2f(-20.f, 0.f);
    }
    else if (keyStatus[sf::Keyboard::Right] && direction != Direction::Left)
    {
        direction = Direction::Right;
        directionVector = sf::Vector2f(20.f, 0.f);
    }
}

sf::Vector2f Snake::getHeadPosition() const
{
    return body[0].getPosition();
}

sf::Vector2f Snake::getBodyPosition(std::size_t index) const
{
    if (index < body.size())
    {
        return body[index].getPosition();
    }
    return sf::Vector2f(-1.f, -1.f); // Om index är ogiltigt
}

std::size_t Snake::getSize() const
{
    return body.size();
}

void Snake::setDirection(Direction dir)
{
    direction = dir;
}

Snake::Direction Snake::getDirection() const
{
    return direction;
}
