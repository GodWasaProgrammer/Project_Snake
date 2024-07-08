#include "Snake.h"

Snake::Snake() : direction(Right)
{
    // Startposition för ormen
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

    // Kontrollera kollision med väggar
    if (headPosition.x < 0 || headPosition.x >= 800 || headPosition.y < 0 || headPosition.y >= 600)
    {
        return true;
    }

    // Kontrollera kollision med kroppen
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction != Down)
    {
        direction = Up;
        directionVector = sf::Vector2f(0.f, -20.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction != Up)
    {
        direction = Down;
        directionVector = sf::Vector2f(0.f, 20.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction != Right)
    {
        direction = Left;
        directionVector = sf::Vector2f(-20.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction != Left)
    {
        direction = Right;
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
    return sf::Vector2f(-1.f, -1.f); // Om indexet är ogiltigt
}

std::size_t Snake::getSize() const
{
    return body.size();
}