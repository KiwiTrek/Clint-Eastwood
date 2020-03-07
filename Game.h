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

/*Si hac�is otras clases, incluid su header aqu�*/
#include "Entity.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960
#define MAX_KEYS 256



class Game
{
	//Variable declaration
	//A�adid las que vayais a necesitar que tengan que ver directamente con Game.
	//Si es de entity, por ejemplo, a entity.
	//Las entities en si misma S� que se han de declarar aqu�
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* windowSurface = nullptr;

	//Used to make the title, and subtitle, and intro music, and other cool shit :^)
	SDL_Surface* title = NULL;
	SDL_Surface* truth = NULL;
	SDL_Surface* enterToStart = NULL;
	SDL_Surface* logo = NULL;

	SDL_Texture* texture = NULL;
	SDL_Texture* textureTruth = NULL;
	SDL_Texture* textureEnterToStart = NULL;
	SDL_Texture* textureLogo = NULL;

	SDL_Rect titleCard = { 0,200,1,235 };
	SDL_Rect truthCard = { 100,550,1080,75 };
	SDL_Rect enterToStartCard = { 540,800,200,75 };
	SDL_Rect logoCard = { 1205,885,75,75 };

	Mix_Music* introMusic = NULL;

	bool present = true; //Aids the press enter to start thing
	/////////////////////////////////////////////////////////////////////////////
	//	MAIN GAME
	Entity test;

public:
	Game();
	~Game();	

	bool Init();		//Initialize Subsystems
						//TAMBI�N ES EL LOAD MEDIA (para cargar im�genes y texturas)
	
	bool introScreen(); //Creates intro screen
	bool intro = true;	//False inicia el juego


	bool Input();		//Aqu� deber�an estar todos lo relacionado con inputs
						//Para movimiento horizontal como el profe (YES IM SORRY ABRAHAM IM A FUCKING PUSSY)
						//Para movimiento vertical como el ejercicio de las pelotas
						//Para otras acciones, haced "acci�n = true" y luego en l�gica/donde la necesiteis la creais
						

	bool Logic();		//Aqu� ir�a todo lo relacionado con la f�sica, la AI, saltos, QTE, etc.
	void Render();		//Los render copies, los sonidos, las animaciones...
						//Para probar Logic sobretodo movimiento, haced "SDL_RenderSetDrawColor" y "SDL_RenderFillRect" para los placeholders.
						//Las rects que solo servir�n para renderizar, dentro del render mismo
	bool Update();
	//Incluso si son de otras clases, todo se deber�a de hacer aqu�
	//S� no quer�is llenar el c�digo de mucho, siempre se puede crear una funci�n para la clase e invocarla en el Logic/Render
	//Pero al final el loop son el Input, el Logic y el Render (en ese orden)

	void CleanUp();		//Close subsystems



	enum KEY_STATE { KEY_IDLE, KEY_DOWN, KEY_REPEAT, KEY_UP };
	KEY_STATE keys[MAX_KEYS];
};