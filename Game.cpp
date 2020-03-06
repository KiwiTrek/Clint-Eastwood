#include "Game.h"

Game::Game() {};
Game::~Game() {};

bool Game::Init() {
	int flags = 0;
	
	//Init Everything
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init: Could not initialize. Error: " << SDL_GetError() << std::endl;
		return false;
	}


	//Window
	window = SDL_CreateWindow(
		"Volley Masters!",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);

	windowSurface = SDL_GetWindowSurface(window);  //Creates surface

	if (window == NULL) {
		std::cout << "Window: Could not initialize. Error: " << SDL_GetError() << std::endl;
		return false;
	}


	//Render
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cout << "Renderer: Could not initialize. Error: " << SDL_GetError() << std::endl;
		return false;
	}


	//SDL_Image
	flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	if ((IMG_Init(flags) & flags) != flags) {
		std::cout << "IMG_Init: Support not created. Error: " << IMG_GetError() << std::endl;
		return false;
	}
	flags = 0;

	//SDL_Mix
	flags = MIX_INIT_OGG;
	if ((Mix_Init(flags) & flags) != flags) {
		std::cout << "Mix_Init: Support not created. Error: " << Mix_GetError() << std::endl;
		return false;
	}
	else {
		if (Mix_OpenAudio(
			MIX_DEFAULT_FREQUENCY,
			MIX_DEFAULT_FORMAT,
			2,
			1024) == -1) {
			std::cout << "Mix_OpenAudio: Support not created. Error: " << Mix_GetError() << std::endl;
			return false;
		}
	}
	flags = 0;
	title = IMG_Load("Resources/VolleyMasters.png");
	truth = IMG_Load("Resources/Truth.png");
	enterToStart = IMG_Load("Resources/EnterToStart.png");
	logo = IMG_Load("Resources/logo.png");

	texture = SDL_CreateTextureFromSurface(renderer, title);
	textureTruth = SDL_CreateTextureFromSurface(renderer, truth);
	textureEnterToStart = SDL_CreateTextureFromSurface(renderer, enterToStart);
	textureLogo = SDL_CreateTextureFromSurface(renderer, logo);
	return true;
}

bool Game::introScreen() {
	//Fill background
	SDL_SetRenderDrawColor(renderer, 0xBB, 0xFF, 0xFF, 1);
	SDL_RenderFillRect(renderer, NULL);

	//Create rectangles
	SDL_Rect cardRects[WINDOW_WIDTH];
	SDL_Rect leftRect[6];
	SDL_Rect coverUp = { 540,800,200,75 };
	

	for (int i = 0; i < 3; i++)
	{
		leftRect[i] = { -WINDOW_WIDTH, 100 + i * 50, WINDOW_WIDTH, 20 };
	}
	for (int i = 3; i < 6; i++)
	{
		leftRect[i] = { -WINDOW_WIDTH, 250 + i * 50, WINDOW_WIDTH, 20 };
	}

	//Animation, I guess (And music, too :/)
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 1);
	introMusic = Mix_LoadMUS("Resources/Intro.wav");
	Mix_PlayMusic(introMusic, 1);
	for (int i = 0; i < WINDOW_WIDTH; i++)
	{
		titleCard.x = i;
		for (int i = 0; i < 6; i++)
		{
			leftRect[i].x++;

			SDL_RenderDrawRect(renderer, &leftRect[i]);
		}
		cardRects[i] = { -55 + i,0,1,235 };

		SDL_RenderCopy(renderer, texture, &cardRects[i], &titleCard);
		SDL_RenderPresent(renderer);
	}

	SDL_Delay(700);
	SDL_RenderCopy(renderer, textureTruth, NULL, &truthCard);
	SDL_RenderCopy(renderer, textureLogo, NULL, &logoCard);
	SDL_RenderPresent(renderer);
	SDL_Delay(500);

	while (intro)
	{
		
		//Makes "Press enter to start appear and disappear"
		if (present)
		{
			SDL_RenderCopy(renderer, textureEnterToStart, NULL, &enterToStartCard);
			present = false;
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 0xBB, 0xFF, 0xFF, 1);
			SDL_RenderFillRect(renderer, &coverUp);
			SDL_RenderDrawRect(renderer, &coverUp);
			present = true;
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(700);
	}



	return true;
}

//bool Game::Input(){}  //No dejaba iniciar porque no devuelve nada, asi que lo comento por ahora -Luce


bool Game::Logic() {
	return false;
}


void Game::Render()
{

}


void Game::CleanUp() {
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}