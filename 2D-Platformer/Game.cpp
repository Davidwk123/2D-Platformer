#include "Game.h"

void Game::initVariables()
{
	groundHeight = window->getSize().y - player.getGlobalBounds().height;

	currentVelocity.x = 0.f, currentVelocity.y = 0.f;
	speed.x = 0.f, speed.y = 0.f;
	maxVelocityG = 10.f;
	maxVelocity = 5.f;
	acceleration = .6f;
	drag = .3f;

	isJumping = false;
	isGround = false;
	endGame = false;

	multiplier = 60.f;
}

void Game::initWindow()
{
	videoMode.width = 800;
	videoMode.height = 600;
	window = new RenderWindow(videoMode, "2D-Platformer", Style::Default);

	window->setFramerateLimit(60);
	window->setKeyRepeatEnabled(false);
}

void Game::initPlayer()
{
	player.setSize(Vector2f(25.f, 50.f));
	player.setFillColor(Color::Green);
	player.setPosition(660.f,
		window->getSize().y - player.getGlobalBounds().height);

	playerOuter.setSize(Vector2f(25.f, 50.f));
	playerOuter.setFillColor(Color::Red);
}

void Game::initWalls()
{
	Wall wall1(50.f, 10.f, 100.f, window->getSize().y - 85.f);
	walls.push_back(wall1);
	Wall wall2(50.f, 10.f, 300.f, window->getSize().y - 250.f);
	walls.push_back(wall2);
	Wall wall3(50.f, 10.f, 50.f, window->getSize().y - 360.f);
	walls.push_back(wall3);
	Wall wall4(200.f, 10.f, 315.f, window->getSize().y - 430.f);
	walls.push_back(wall4);
	Wall wall5(50.f, 10.f, 650.f, window->getSize().y - 480.f);
	walls.push_back(wall5);
}

void Game::initMark()
{
	mark.setSize(Vector2f(15.f, 15.f));
	mark.setFillColor(Color::Red);
	mark.setPosition(window->getSize().x - 50.f, 25.f);
}

void Game::initFont()
{
	if (!(endGameFont.loadFromFile("TimesNewerRoman-Regular.otf")));
	{
		// Error
	}
}

void Game::initText()
{
	initFont();
	endGameText.setFont(endGameFont);
	endGameText.setString("Game Over!\n Press r to restart.");
	endGameText.setPosition((window->getSize().x / 2) - endGameText.getGlobalBounds().width / 2, window->getSize().y / 2);
	endGameText.setCharacterSize(24);
	endGameText.setFillColor(sf::Color::Red);
	endGameText.setStyle(sf::Text::Bold);
}

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

bool Game::running()
{
	return window->isOpen();
}

float Game::deltaTimeFunction(float deltaTime){return deltaTime * multiplier;}

void Game::movement(float deltaTime)
{

	// Jump
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		if ((currentVelocity.y == 0 && isJumping == true && player.getPosition().y == groundHeight)
		|| (currentVelocity.y == 0 && isJumping == true && isGround == true)) {

			speed.y = -16.4f;

			currentVelocity.y += speed.y * deltaTimeFunction(deltaTime);
		}
		else {
			isJumping = false;  
			isGround = false;
		}
	}
	// Gravity
	if (player.getPosition().y < groundHeight) {

		speed.y = 1.2f;

		if (currentVelocity.y < maxVelocityG) {
			currentVelocity.y += acceleration * speed.y * deltaTimeFunction(deltaTime);
			
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		speed.x = -1.3f;

		if (currentVelocity.x > -maxVelocity)
			currentVelocity.x += acceleration * speed.x * deltaTimeFunction(deltaTime);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		speed.x = 1.3f;
		
		if (currentVelocity.x < maxVelocity) {
			currentVelocity.x += acceleration * speed.x * deltaTimeFunction(deltaTime);
			
		}
	}
	
}

void Game::dragMovement(float deltaTime)
{
	// Right
	if (currentVelocity.x > 0.f) {
		currentVelocity.x -= drag * deltaTimeFunction(deltaTime);

		if (currentVelocity.x < 0.f)
			currentVelocity.x = 0.f;
	}
	// Left
	else if (currentVelocity.x < 0.f) {
		currentVelocity.x += drag * deltaTimeFunction(deltaTime);

		if (currentVelocity.x > 0.f)
			currentVelocity.x = 0.f;
	}
	// Down
	else if (currentVelocity.y >= 0.f) {
		currentVelocity.y -= drag * deltaTimeFunction(deltaTime);

		if (currentVelocity.y < 0.f)
			currentVelocity.y = 0.f;
	}
	// Up
	else if (currentVelocity.y < 0.f) {
		currentVelocity.y += drag * deltaTimeFunction(deltaTime);

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
	
	// playerOuter.setPosition(nextPos.left,
	// 	nextPos.top);

	for (Wall i : walls) {
		wallBounds = i.getShape().getGlobalBounds();
		
		if (wallBounds.intersects(nextPos)) {
			
			// Top + height = bottom 
			// Left + width = right

			// Player bottom 
			if (playerBounds.top < wallBounds.top && playerBounds.left + playerBounds.width > wallBounds.left 
			&& playerBounds.left < wallBounds.left + wallBounds.width
				/*&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
				&& playerBounds.left < wallBounds.left + wallBounds.width
				&& playerBounds.left + playerBounds.width > wallBounds.left*/) {

				currentVelocity.y = 0.f;
				player.setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
				isGround = true;
			}
			// Player top
			if (playerBounds.top > wallBounds.top && playerBounds.left + playerBounds.width > wallBounds.left 
			&& playerBounds.left < wallBounds.left + wallBounds.width
				/*&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
				&& playerBounds.left < wallBounds.left + wallBounds.width
				&& playerBounds.left + playerBounds.width > wallBounds.left*/) {
				
				currentVelocity.y = 0.f;
				player.setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
			}

			// Player right
			if (playerBounds.left < wallBounds.left && playerBounds.top + playerBounds.height > wallBounds.top
			&& playerBounds.top < wallBounds.top /*
				&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
				&& playerBounds.top < wallBounds.top + wallBounds.height
				&& playerBounds.top + playerBounds.height > wallBounds.top*/) {

				currentVelocity.x = 0.f;
				player.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);

			}

			// Player left
			if (playerBounds.left > wallBounds.left && playerBounds.top + playerBounds.height > wallBounds.top
			&& playerBounds.top < wallBounds.top/*
				&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
				&& playerBounds.top < wallBounds.top + wallBounds.height
				&& playerBounds.top + playerBounds.height > wallBounds.top*/) {

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
		endGame = true;
		currentVelocity.x = 0.f;
		currentVelocity.y = 0.f;
		player.setPosition(660.f,
			window->getSize().y - player.getGlobalBounds().height);
	}
}

void Game::screenCollision()
{
	// Left
	if (player.getPosition().x <= 0) {
		player.setPosition(0, player.getPosition().y);
	}
	// Right
	if (player.getPosition().x >= window->getSize().x
		- player.getGlobalBounds().width)
		player.setPosition(window->getSize().x -
			player.getGlobalBounds().width,
			player.getPosition().y);
	// Top
	if (player.getPosition().y <= 0) {
		player.setPosition(player.getPosition().x, 0);
		currentVelocity.y = 0.f;
	}
	// Bottom
	if (player.getPosition().y > groundHeight) {
		player.setPosition(player.getPosition().x,
			groundHeight);
		//allows constant jump height
		currentVelocity.y = 0.f;
	}
}

void Game::checkEvents()
{
	while (window->pollEvent(event)) {

		// Exiting program
		if (event.type == Event::Closed)
			window->close();
		// Retry program
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::R)
			endGame = false;
		// Jump spam counter
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
			isJumping = true;
	}
}

void Game::update()
{
	checkEvents();
	// Get computers's deltatime 
	dt = clock.restart().asSeconds(); 
	// Keeps going until all extra timesteps are done 
	while(dt > 0.0f){ 
		// Get program's desired deltatime
		float deltaTime = min(dt, 1.0f/60.0f); 
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

void Game::render()
{
	if (endGame == false)
	{
		window->clear();
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
