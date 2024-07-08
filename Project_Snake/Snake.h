#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <deque>

class Snake
{
public:
	Snake();
	void move();
	void grow();
	void update();
	void render(sf::RenderWindow& window);
	bool checkCollision();
	sf::Vector2f getHeadPosition() const;

private:
	enum Direction { Up, Down, Left, Right };
	Direction direction;
	std::deque<sf::RectangleShape> body;
	sf::Vector2f directionVector;
	sf::RectangleShape createSegment(float x, float y);
	void updateDirection();
};
#endif // !SNAKE_H