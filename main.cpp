#include "Game.h"

int main(int argc, char* argv[]) {
	Game game;
	if (!game.Init()) return -1;

	bool quit = false;
	if (game.introScreen()) {
		while (!quit)
		{

			quit = game.Logic();
			if (!game.intro) { game.Render(); }   //Game intro, the game itself

		}
	}
	game.CleanUp();
	return 0;
}