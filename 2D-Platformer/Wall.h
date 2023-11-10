#ifndef WALL_H
#define WALL_H

#include<SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class Wall
{
public:
	Wall();
	Wall(float width1, float height1, float x1, float y1);

	RectangleShape getShape();

private:
	RectangleShape wall;
	float width, height, x, y;
};
#endif