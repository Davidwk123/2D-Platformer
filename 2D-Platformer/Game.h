#ifndef GAME_H
#define GAME_H

#include "Wall.h"
#include <SFML\Graphics.hpp>
#include <vector>
#include <string>

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
	// Used for collision detection debugging
	RectangleShape playerOuter;
	// End goal for player 
	RectangleShape mark;
	vector<Wall> walls;
	Font endGameFont;
	Text endGameText;

	/*
	* Movement variables
	*/
	Vector2f currentVelocity;
	Vector2f speed;
	bool isJumping;
	bool isGrounded;
	bool didGameEnd;

	/*
	* Fps and collision variables 
	*/
	Clock clock;
	float dt;
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

	/*
	* Constants
	*/
	string GAME_TITLE = "2D-Platformer";
	int WINDOW_WIDTH = 1024;
	int WINDOW_HEIGHT = 576;

	int FPS = 30;
	float MULTIPLIER = 60.f;

	float PLAYER_START_X = WINDOW_WIDTH/2;
	float PLAYER_START_Y = WINDOW_HEIGHT - PLAYER_HEIGHT;
	float PLAYER_WIDTH = 25.f;
	float PLAYER_HEIGHT = 50.f;
	Color PLAYER_COLOR = Color::Green;

	float MARK_START_X = WINDOW_WIDTH - 50.f;
	float MARK_START_Y = 25.f;
	float MARK_WIDTH = 15.f;
	float MARK_HEIGHT = 15.f;
	Color MARK_COLOR = Color::Red;

	float GROUND_HEIGHT = WINDOW_HEIGHT - PLAYER_HEIGHT;
	float MAX_VELOCITY_GRAVITY = 10.f;
	float MAX_VELOCITY_MOVEMENT = 5.f;
	float ACCELERATION = .6f;
	float DRAG = .3f;

	string FONT_FILE = "TimesNewerRoman-Regular.otf";


};
#endif