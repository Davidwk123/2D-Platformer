#include "Game.h"
#include <algorithm>

Game::Game()
{
	initWindow();
	initPlayer();
	initVariables();

	initWalls();
	initMark();
	initText();
}

Game::~Game()
{
	delete window;
}

void Game::initVariables()
{
	currentVelocity.x = 0.f, currentVelocity.y = 0.f;
	speed.x = 0.f, speed.y = 0.f;

	isJumping = false;
	isGrounded = false;
	didGameEnd = false;
}

void Game::initWindow()
{
	videoMode.width = WINDOW_WIDTH;
	videoMode.height = WINDOW_HEIGHT;
	window = new RenderWindow(videoMode, GAME_TITLE, Style::Titlebar | Style::Close);

	window->setFramerateLimit(FPS);
	window->setKeyRepeatEnabled(false);
}

void Game::initPlayer()
{
	player.setSize(Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
	player.setFillColor(PLAYER_COLOR);
	player.setPosition(PLAYER_START_X, PLAYER_START_Y);

	// For debug
	/*playerOuter.setSize(Vector2f(25.f, 50.f));
	playerOuter.setFillColor(Color::Red);*/
}

void Game::initWalls()
{
	Wall wall1(50.f, 10.f, 0.f, WINDOW_HEIGHT - 150.f);
	walls.push_back(wall1);
	Wall wall2(50.f, 10.f, 100.f, WINDOW_HEIGHT - 300.f);
	walls.push_back(wall2);
	Wall wall3(50.f, 10.f, 150.f, WINDOW_HEIGHT - 450.f);
	walls.push_back(wall3);
	Wall wall4(50.f, 10.f, 300.f, WINDOW_HEIGHT - 300.f);
	walls.push_back(wall4);
	Wall wall5(50.f, 10.f, 550.f, WINDOW_HEIGHT - 300.f);
	walls.push_back(wall5);
	Wall wall6(50.f, 10.f, 800.f, WINDOW_HEIGHT - 325.f);
	walls.push_back(wall6);
	
}

void Game::initMark()
{
	mark.setSize(Vector2f(MARK_WIDTH, MARK_HEIGHT));
	mark.setFillColor(MARK_COLOR);
	mark.setPosition(MARK_START_X, MARK_START_Y);
}

void Game::initFont()
{
	if (!(endGameFont.loadFromFile(FONT_FILE)));
	{
		// Error
	}
}

void Game::initText()
{
	initFont();
	endGameText.setFont(endGameFont);
	endGameText.setString("\tGame Over!\nPress 'r' to restart...");
	endGameText.setPosition((WINDOW_WIDTH / 2.f) - (endGameText.getGlobalBounds().width / 2.f),
		(WINDOW_HEIGHT / 2.f) - (endGameText.getGlobalBounds().height / 2.f));
	endGameText.setCharacterSize(40);
	endGameText.setFillColor(sf::Color::Red);
	endGameText.setStyle(sf::Text::Bold);
}

bool Game::running()
{
	return window->isOpen();
}

float Game::deltaTimeFunction(float deltaTime)
{
	return deltaTime * MULTIPLIER;
}

void Game::movement(float deltaTime)
{

	// Jump
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		if ((currentVelocity.y == 0 && isJumping == true && player.getPosition().y == GROUND_HEIGHT)
		|| (currentVelocity.y == 0 && isJumping == true && isGrounded == true)) {

			speed.y = -16.4f;

			currentVelocity.y += speed.y * deltaTimeFunction(deltaTime);
		}
		else {
			isJumping = false;  
			isGrounded = false;
		}
	}
	// Gravity
	if (player.getPosition().y < GROUND_HEIGHT) {

		speed.y = 1.2f;

		if (currentVelocity.y < MAX_VELOCITY_GRAVITY) {
			currentVelocity.y += ACCELERATION * speed.y * deltaTimeFunction(deltaTime);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		speed.x = -1.3f;

		if (currentVelocity.x > -MAX_VELOCITY_MOVEMENT) {
			currentVelocity.x += ACCELERATION * speed.x * deltaTimeFunction(deltaTime);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		speed.x = 1.3f;
		
		if (currentVelocity.x < MAX_VELOCITY_MOVEMENT) {
			currentVelocity.x += ACCELERATION * speed.x * deltaTimeFunction(deltaTime);
		}
	}
	
}

void Game::dragMovement(float deltaTime)
{
	// Right
	if (currentVelocity.x > 0.f) {
		currentVelocity.x -= DRAG * deltaTimeFunction(deltaTime);

		if (currentVelocity.x < 0.f)
			currentVelocity.x = 0.f;
	}
	// Left
	else if (currentVelocity.x < 0.f) {
		currentVelocity.x += DRAG * deltaTimeFunction(deltaTime);

		if (currentVelocity.x > 0.f)
			currentVelocity.x = 0.f;
	}
	// Down
	else if (currentVelocity.y >= 0.f) {
		currentVelocity.y -= DRAG * deltaTimeFunction(deltaTime);

		if (currentVelocity.y < 0.f)
			currentVelocity.y = 0.f;
	}
	// Up
	else if (currentVelocity.y < 0.f) {
		currentVelocity.y += DRAG * deltaTimeFunction(deltaTime);

		if (currentVelocity.y > 0.f)
			currentVelocity.y = 0.f;
	}
}

void Game::wallCollision()
{
	playerBounds = player.getGlobalBounds();
	nextPos = playerBounds;

	nextPos.left += currentVelocity.x;
	nextPos.top += currentVelocity.y;
	
	// Debug 
	// playerOuter.setPosition(nextPos.left,
	// 	nextPos.top);

	for (Wall i : walls) {
		wallBounds = i.getShape().getGlobalBounds();
		
		if (wallBounds.intersects(nextPos)) {
			
			// Top + height = bottom 
			// Left + width = right

			// Player bottom 
			if (playerBounds.top < wallBounds.top && playerBounds.left + playerBounds.width > wallBounds.left 
			&& playerBounds.left < wallBounds.left + wallBounds.width) {

				currentVelocity.y = 0.f;
				player.setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
				isGrounded = true;
			}
			// Player top
			else if (playerBounds.top > wallBounds.top && playerBounds.left + playerBounds.width > wallBounds.left 
			&& playerBounds.left < wallBounds.left + wallBounds.width) {
				
				currentVelocity.y = 0.f;
				player.setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
			}
			// Player right
			else if (playerBounds.left < wallBounds.left && playerBounds.top + playerBounds.height > wallBounds.top
			&& playerBounds.top < wallBounds.top) {

				currentVelocity.x = 0.f;
				player.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);

			}
			// Player left
			else if (playerBounds.left > wallBounds.left && playerBounds.top + playerBounds.height > wallBounds.top
			&& playerBounds.top < wallBounds.top) {

				currentVelocity.x = 0.f;
				player.setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
			}
		}
	}
}

void Game::markCollision()
{
	if (playerBounds.intersects(mark.getGlobalBounds()))
	{
		didGameEnd = true;
		currentVelocity.x = 0.f;
		currentVelocity.y = 0.f;
		player.setPosition(PLAYER_START_X, PLAYER_START_Y);
	}
}

void Game::screenCollision()
{
	// Left
	if (player.getPosition().x <= 0) {
		player.setPosition(0, player.getPosition().y);
	}
	// Right
	if (player.getPosition().x >= WINDOW_WIDTH - PLAYER_WIDTH) {
		player.setPosition(WINDOW_WIDTH - PLAYER_WIDTH, player.getPosition().y);
	}
	// Top
	if (player.getPosition().y <= 0) {
		player.setPosition(player.getPosition().x, 0);
		currentVelocity.y = 0.f;
	}
	// Bottom
	if (player.getPosition().y > GROUND_HEIGHT) {
		player.setPosition(player.getPosition().x, GROUND_HEIGHT);
		// Allows constant jump height
		currentVelocity.y = 0.f;
	}
}

void Game::checkEvents()
{
	while (window->pollEvent(event)) {

		// Exiting program
		if (event.type == Event::Closed) {
			window->close();
		}
		// Retry program
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::R){
			didGameEnd = false;

		}
		// Jump spam counter
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space){
			isJumping = true;

		}
	}
}

void Game::update()
{
	checkEvents();

	// Get computers's deltatime 
	dt = clock.restart().asSeconds();

	// Check if user made it to the end of the level
	if (didGameEnd == false)
	{
		// Keeps going until all extra timesteps are done 
		while (dt > 0.0f) {
			// Get program's desired deltatime
			float deltaTime = min(dt, 1.0f / MULTIPLIER);
			// Desired timesteps computer needs to take to match with the program's dt 
			dt -= deltaTime;
			movement(deltaTime);
			dragMovement(deltaTime);
			wallCollision();
			markCollision();
			player.move(currentVelocity * deltaTimeFunction(deltaTime));
			// Causes player to glitch near the edges of the screen if function is put before player.move 
			screenCollision();
		}
	}
}

void Game::render()
{
	if (didGameEnd == false)
	{
		window->clear();
		// Debug
		//window->draw(playerOuter); For testing players movement 
		window->draw(player);
		
		window->draw(mark);

		for (Wall i : walls) {
			window->draw(i.getShape());
		}
		window->display();
	}
	else 
	{
		window->clear();
		window->draw(endGameText);
		window->display();
	}
}
