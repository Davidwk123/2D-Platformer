#include<iostream>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include<math.h>
#include<vector>
#include<cstdlib>
using namespace std;
using namespace sf;

class Wall
{
	private:
		RectangleShape wall;
		float width, height, x, y;

	public:
		Wall()
		{
			width = 0;
			height = 0;
			x = 0;
			y = 0;

			wall.setSize(Vector2f(width, height));
			wall.setFillColor(Color::White);
			wall.setPosition(x, y);
		}

		Wall(float width1, float height1, float x1, float y1)
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

		RectangleShape getShape()
		{
			return wall;
		}

};