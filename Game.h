#pragma once
#include <stdio.h>
#include <iostream>

#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"
#include "SDL_Mixer/include/SDL_mixer.h"

#pragma comment(lib,"SDL/libx86/SDL2.lib")
#pragma comment(lib,"SDL/libx86/SDL2main.lib")
#pragma comment(lib,"SDL_Image/libx86/SDL2_image.lib")
#pragma comment(lib,"SDL_Mixer/libx86/SDL2_mixer.lib")

/*Si hacéis otras clases, incluid su header aquí*/
#include "Entity.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960
#define MAX_KEYS 256



class Game
{
	//Variable declaration
	//Añadid las que vayais a necesitar que tengan que ver directamente con Game.
	//Si es de entity, por ejemplo, a entity.
	//Las entities en si misma SÍ que se han de declarar aquí
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* windowSurface = nullptr;

	//Used to make the title, and subtitle, and intro music, and other cool shit :^)
	SDL_Surface* title = NULL;
	SDL_Surface* truth = NULL;
	SDL_Surface* enterToStart = NULL;
	SDL_Surface* logo = NULL;
	SDL_Surface* player1Controls = NULL;
	SDL_Surface* player2Controls = NULL;
	SDL_Surface* PE2Q = NULL;

	SDL_Texture* texture = NULL;
	SDL_Texture* textureTruth = NULL;
	SDL_Texture* textureEnterToStart = NULL;
	SDL_Texture* textureLogo = NULL;
	SDL_Texture* tP1C = NULL;
	SDL_Texture* tP2C = NULL;
	SDL_Texture* tPE2Q = NULL;

	SDL_Rect titleCard = { 0,200,1,235 };
	SDL_Rect truthCard = { 100,550,1080,75 };
	SDL_Rect enterToStartCard = { 540,800,200,75 };
	SDL_Rect logoCard = { 1205,885,75,75 };
	SDL_Rect P1CCard = { 20,610,300,300 };
	SDL_Rect P2CCard = { 960,610,300,300 };
	SDL_Rect PE2QCard = { 440,900,400,30 };


	Mix_Music* introMusic = NULL;
	Mix_Music* gameMusic = NULL;
	Mix_Chunk* ohYes = NULL;

	//Scoreboard
	SDL_Surface* numbers[10] = {};
	SDL_Texture* tNumbers[10] = {};
	//Player1
	SDL_Rect numbersCard1 = { 450,0,50,50 };
	SDL_Rect numbersCard2 = { 510,0,50,50 };
	//Player2
	SDL_Rect numbersCard3 = { 720,0,50,50 };
	SDL_Rect numbersCard4 = { 780,0,50,50 };

	int score1[2] = { 0,0 };
	int score2[2] = { 0,0 };

	//Game texts and sound effects
	int points = 0;

	Mix_Chunk* getReady = NULL;
	Mix_Chunk* playBall = NULL;
	Mix_Chunk* game = NULL;

	SDL_Surface* sGetReady = NULL;
	SDL_Surface* sPlayBall = NULL;
	SDL_Surface* sGame = NULL;
	SDL_Surface* sPoint = NULL; //No sfx, yet
	SDL_Surface* sP1Wins = NULL;
	SDL_Surface* sP2Wins = NULL;

	SDL_Texture* tGetReady = NULL; 
	SDL_Texture* tPlayBall = NULL; 
	SDL_Texture* tGame = NULL;
	SDL_Texture* tPoint = NULL;
	SDL_Texture* tP1Wins = NULL;
	SDL_Texture* tP2Wins = NULL;

	SDL_Rect multiCard = { 590,100,100,50 };
	SDL_Rect playerWins = { 490,200,300,100 };

	/////////////////////////////////////////////////////////////////////////////
	//	MAIN GAME
	Entity ball;
	SDL_Surface* ballSur;
	SDL_Texture* ballTxt;

	Entity player1;
	SDL_Surface* player1surIdle;
	SDL_Texture* player1txtIdle;

	SDL_Surface* player1surJump;
	SDL_Texture* player1txtJump;

	SDL_Surface* player1surLeft;
	SDL_Texture* player1txtLeft;

	SDL_Surface* player1surRight;
	SDL_Texture* player1txtRight;


	Entity player2;
	SDL_Surface* player2surIdle;
	SDL_Texture* player2txtIdle;

	SDL_Surface* player2surJump;
	SDL_Texture* player2txtJump;

	SDL_Surface* player2surLeft;
	SDL_Texture* player2txtLeft;

	SDL_Surface* player2surRight;
	SDL_Texture* player2txtRight;

	Entity net;
	SDL_Surface* netSur;
	SDL_Texture* netTxt;

	SDL_Surface* bgSurface;
	SDL_Texture* bgTxt;

public:
	Game();
	~Game();	

	bool Init();		//Initialize Subsystems
						//TAMBIÉN ES EL LOAD MEDIA (para cargar imágenes y texturas)
	
	bool introScreen(); //Creates intro screen
	bool intro = true;	//False inicia el juego


	bool Input();		//Aquí deberían estar todos lo relacionado con inputs
						//Para movimiento horizontal como el profe (YES IM SORRY ABRAHAM IM A FUCKING PUSSY)
						//Para movimiento vertical como el ejercicio de las pelotas
						//Para otras acciones, haced "acción = true" y luego en lógica/donde la necesiteis la creais
						

	bool Logic();		//Aquí iría todo lo relacionado con la física, la AI, saltos, QTE, etc.

	void Scoreboard();

	bool winCondition();
	bool win = false;

	void Render();		//Los render copies, los sonidos, las animaciones...
						//Para probar Logic sobretodo movimiento, haced "SDL_RenderSetDrawColor" y "SDL_RenderFillRect" para los placeholders.
						//Las rects que solo servirán para renderizar, dentro del render mismo
	bool Update();
	//Incluso si son de otras clases, todo se debería de hacer aquí
	//Sí no queréis llenar el código de mucho, siempre se puede crear una función para la clase e invocarla en el Logic/Render
	//Pero al final el loop son el Input, el Logic y el Render (en ese orden)

	void CleanUp();		//Close subsystems



	enum KEY_STATE { KEY_IDLE, KEY_DOWN, KEY_REPEAT, KEY_UP };
	KEY_STATE keys[MAX_KEYS];
	enum ID {ID_PLAYER, ID_BALL, ID_NET};
	SDL_Rect player1animations[24] = {};
	SDL_Rect player2animations[24] = {};
};