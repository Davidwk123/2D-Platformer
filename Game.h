#ifndef GAME_H
#define GAME_H

#include<iostream>
#include <vector>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include<math.h>
#include<vector>
#include<cstdlib>
#include "Wall.cpp"

using namespace std;
using namespace sf;

class Game
{
private:
	//Window and Events
	RenderWindow* window;
	VideoMode videoMode;
	Event event;

	//objects
	RectangleShape player;
	RectangleShape playerOuter;
	RectangleShape mark;
	vector<Wall> walls;
	Font endGameFont;
	Text endGameText;

	//movement variables
	float groundHeight;
	Vector2f currentVelocity;
	Vector2f speed;
	float maxVelocityG;
	float maxVelocity;
	float acceleration;
	float drag;
	bool isJumping;
	bool isGround;
	bool endGame;

	//fps and collision variables
	Clock clock;
	float dt;
	float multiplier;
	FloatRect playerBounds;
	FloatRect wallBounds;
	FloatRect nextPos;

	//intialize functions
	void initVariables();
	void initPlayer();
	void initWalls();
	void initMark();
	void initFont();
	void initText();
	void initWindow();

	//movement and coliision functions
	void movement(float deltaTime);
	float deltaTimeFunction(float del);
	void dragMovement(float deltaTime);
	void wallCollision();
	void markCollision();
	void screenCollision();

public:
	Game();
	virtual ~Game();

	bool running();

	void pollEvents();
	void update();
	void render();

};


#endif