#include "Game.h"

int SDL_main(int argc, char* argv[])
{
	Game* game = new Game();

	game->Update();

	delete game;
	
	return 0;
}