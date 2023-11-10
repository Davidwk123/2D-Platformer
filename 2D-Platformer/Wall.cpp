#include "Wall.h"

Wall::Wall()
{
	width = 0;
	height = 0;
	x = 0;
	y = 0;

	wall.setSize(Vector2f(width, height));
	wall.setFillColor(Color::White);
	wall.setPosition(x, y);
}

Wall::Wall(float width1, float height1, float x1, float y1)
{
	// Error checking
	width = width1;
	height = height1;
	x = x1;
	y = y1;

	wall.setSize(Vector2f(width, height));
	wall.setFillColor(Color::White);
	wall.setPosition(x, y);
}

RectangleShape Wall::getShape()
{
	return wall;
}
