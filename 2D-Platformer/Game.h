#ifndef GAME_H
#define GAME_H

#include "Wall.h"
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class Game
{
public:
	Game();

	virtual ~Game();

	// Returns whether game window is getting dispalyed or not
	bool running();

	// Check game events like user input or exiting game
	void checkEvents();

	// Called every frame to update game objects
	void update();

	// Applies all changes from update() function and displays it to game window 
	void render();

private:
	/*
	* Window and Events
	*/
	RenderWindow* window;
	VideoMode videoMode;
	Event event;

	/*
	* Objects
	*/
	RectangleShape player;
	RectangleShape playerOuter;
	RectangleShape mark;
	vector<Wall> walls;
	Font endGameFont;
	Text endGameText;

	/*
	* Movement variables
	*/
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

	/*
	* Fps and collision variables 
	*/
	Clock clock;
	float dt;
	float multiplier;
	FloatRect playerBounds;
	FloatRect wallBounds;
	FloatRect nextPos;

	/*
	* Initialize functions 
	*/
	void initVariables();
	void initPlayer();
	void initWalls();
	void initMark();
	void initFont();
	void initText();
	void initWindow();

	/*
	* Movement and collision functions 
	*/
	void movement(float deltaTime);
	float deltaTimeFunction(float del);
	void dragMovement(float deltaTime);
	void wallCollision();
	void markCollision();
	void screenCollision();
};
#endif