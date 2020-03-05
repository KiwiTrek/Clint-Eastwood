#include "Game.h"

int main(int argc, char* argv[]) {
	Game game;
	if (!game.Init()) return -1;

	bool quit = false;
	while (!quit)
	{
		quit = game.Logic();
		game.Render();
	}

	game.CleanUp();
	return 0;
}