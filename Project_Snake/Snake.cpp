#include "Snake.h"

Snake::Snake() : direction(Right)
{
	// start position for snake
	body.push_back(createSegment(100.f, 100.f));
	body.push_back(createSegment(80.f, 100.f));
	body.push_back(createSegment(60.f, 100.f));
	
	// movement vector
	directionVector = sf::Vector2f(20.f, 0.f);
}