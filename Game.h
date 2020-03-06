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

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960



class Game
{
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

	bool present = true; //Aids the press enter to star thing

public:
	Game();
	~Game();	

	bool Init();		//Initialize Subsystems
	
	//bool Input();
	bool introScreen(); //Creates intro screen
	bool intro = true;

	bool Logic();
	void Render();		//The render copies

	void CleanUp();		//Close subsystems
};