#include "ConstValue.h"
#include "Game.h"

int main()
{
	Game* game = new Game();

	game->Update();
	delete game;

	return 0;
}