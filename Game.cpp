#include "Game.h"

void Game::initVariables()
{
	groundHeight = window->getSize().y -
		player.getGlobalBounds().height;

	currentVelocity.x = 0.f, currentVelocity.y = 0.f;
	speed.x = 0.f, speed.y = 0.f;
	maxVelocityG = 10.f;
	maxVelocity = 5.f;
	acceleration = .6f;
	drag = .2f;

	isJumping = false;
	endGame = false;

	multiplier = 60.f;
}

void Game::initWindow()
{
	videoMode.width = 800;
	videoMode.height = 600;
	window = new RenderWindow(videoMode, "Platformer", Style::Default);

	window->setFramerateLimit(60);
	window->setKeyRepeatEnabled(false);
}

void Game::initPlayer()
{
	player.setSize(Vector2f(25.f, 50.f));
	player.setFillColor(Color::Green);
	player.setPosition(660.f,
		window->getSize().y - player.getGlobalBounds().height);
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
	if (!(endGameFont.loadFromFile("fonts/TimesNewerRoman-Regular.otf")));
	{
		//error
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

void Game::movement()
{
	dt = clock.restart().asSeconds();
	//jump
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		if (currentVelocity.y == 0 && isJumping == true) {

			speed.y = -15.6f;

			currentVelocity.y += speed.y * dt * multiplier;
		}
		else {
			isJumping = false;
		}
	}
	//gravity
	if (player.getPosition().y < groundHeight) {

		speed.y = 1.2f;

		if (currentVelocity.y < maxVelocityG) {
			currentVelocity.y += acceleration * speed.y * dt * multiplier;
			
		}
	}
	//left
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		speed.x = -1.2f;

		if (currentVelocity.x > -maxVelocity)
			currentVelocity.x += acceleration * speed.x * dt * multiplier;
	}
	//right
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		speed.x = 1.2f;
		
		if (currentVelocity.x < maxVelocity) {
			currentVelocity.x += acceleration * speed.x * dt * multiplier;
			
		}
	}
	
}

void Game::dragMovement()
{
	// right
	if (currentVelocity.x > 0.f) {
		currentVelocity.x -= drag * dt * multiplier;

		if (currentVelocity.x < 0.f)
			currentVelocity.x = 0.f;
	}
	// left
	else if (currentVelocity.x < 0.f) {
		currentVelocity.x += drag * dt * multiplier;

		if (currentVelocity.x > 0.f)
			currentVelocity.x = 0.f;
	}
	// down
	else if (currentVelocity.y >= 0.f) {
		currentVelocity.y -= drag * dt * multiplier;

		if (currentVelocity.y < 0.f)
			currentVelocity.y = 0.f;
	}
	// up
	else if (currentVelocity.y < 0.f) {
		currentVelocity.y += drag * dt * multiplier;

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

	for (Wall i : walls) {
		wallBounds = i.getShape().getGlobalBounds();
		if (wallBounds.intersects(nextPos)) {

			//player bottom 
			if (playerBounds.top < wallBounds.top
				&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
				&& playerBounds.left < wallBounds.left + wallBounds.width
				&& playerBounds.left + playerBounds.width > wallBounds.left) {

				currentVelocity.y = 0.f;
				player.setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
			}
			//player top
			if (playerBounds.top > wallBounds.top
				&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
				&& playerBounds.left < wallBounds.left + wallBounds.width
				&& playerBounds.left + playerBounds.width > wallBounds.left) {

				currentVelocity.y = 0.f;
				player.setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
			}

			//player right

			if (playerBounds.left < wallBounds.left
				&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
				&& playerBounds.top < wallBounds.top + wallBounds.height
				&& playerBounds.top + playerBounds.height > wallBounds.top) {

				currentVelocity.x = 0.f;
				player.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);

			}

			//player left
			if (playerBounds.left > wallBounds.left
				&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
				&& playerBounds.top < wallBounds.top + wallBounds.height
				&& playerBounds.top + playerBounds.height > wallBounds.top) {

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
	// left
	if (player.getPosition().x <= 0) {
		player.setPosition(0, player.getPosition().y);
	}
	// right
	if (player.getPosition().x >= window->getSize().x
		- player.getGlobalBounds().width)
		player.setPosition(window->getSize().x -
			player.getGlobalBounds().width,
			player.getPosition().y);
	// top
	if (player.getPosition().y <= 0) {
		player.setPosition(player.getPosition().x, 0);
		currentVelocity.y = 0.f;
	}
	// bottom
	if (player.getPosition().y > groundHeight) {
		player.setPosition(player.getPosition().x,
			groundHeight);
		//allows constant jump height
		currentVelocity.y = 0.f;
	}
}

void Game::pollEvents()
{
	while (window->pollEvent(event)) {

		//exiting program
		if (event.type == Event::Closed)
			window->close();
		//retry program
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::R)
			endGame = false;
		//jump spam counter
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
			isJumping = true;
	}
}

void Game::update()
{
	pollEvents();
	movement();
	dragMovement();
	wallCollision();
	markCollision();
	player.move(currentVelocity * dt * multiplier);
	screenCollision();
}

void Game::render()
{
	if (endGame == false)
	{
		window->clear();
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
