#include <iostream>
#include "Game.h"

int main()
{
	Game game;

	while (game.running()) {

		//update
		game.update();
		//draw
		game.render();
	}
	return 0;
}
