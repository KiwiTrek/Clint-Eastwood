#include "Game.h"

int main(int argc, char* argv[]) {
	Game game;						//Inicializa la class Game
	if (!game.Init()) return -1;	//Ejecuta game.Init(que es un bool)
									//Si hay alguna parte que no funciona, devuelve false y crashea

	bool quit = false;
	if (game.introScreen()) {		//La intro es una función bool. Si devuelve true, significa que la intro se ha cargado correctamente y empieza el loop.
									//Sino cierra el juego entero
		while (!quit)
		{

			quit = game.Input();		//Hace los inputs del juego
			if (!game.intro) { 
				game.Logic();			//Hace la lógica del juego
				game.Render(); }		//Hace el render

		}
	}
	game.CleanUp();						//Cierra todo
	return 0;
}