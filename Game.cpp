#include "Game.h"

Game::Game() {};
Game::~Game() {};

bool intro = true;
//Used to make the title
SDL_Surface* title = NULL;
SDL_Texture* texture = NULL;

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

	return true;
}



//bool Game::Input(){}  //No dejaba iniciar porque no devuelve nada, asi que lo comento por ahora -Luce


bool Game::Logic() {
	return false;
}


void Game::Render()
{
	//SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window); //Temporary
}


//Intro
bool Game::introScreen()
{
	//Title
	title= IMG_Load("VolleyMasters.png");
	texture = SDL_CreateTextureFromSurface(renderer, title);
	SDL_Rect titleCard = { 200, 200, 400, 200 };

	//Fill background
	SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 0xBB, 0xFF, 0xFF));

	//Create rectangles
	SDL_Rect leftRect[3];
	SDL_Rect rightRect[3];
	for (int i = 0; i < 3; i++)
	{

		leftRect[i] = { -WINDOW_WIDTH, 100 + i * 50, WINDOW_WIDTH, 20 };
		rightRect[i] = { WINDOW_WIDTH, 400 + i * 50, WINDOW_WIDTH, 20 };
		
	}

	//Animation, I guess
	for (int i = 0; i < WINDOW_WIDTH; i++)
	{

		for (int i = 0; i < 3; i++)
		{
			leftRect[i].x++;
			rightRect[i].x--;

			SDL_FillRect(windowSurface, &leftRect[i], SDL_MapRGB(windowSurface->format, 0xFF, 0xFF, 0xFF));
			SDL_FillRect(windowSurface, &rightRect[i], SDL_MapRGB(windowSurface->format, 0xFF, 0xFF, 0xFF));
		}
		
		Render();
	}

	SDL_RenderCopy(renderer, texture, NULL, &titleCard);
	//SDL_RenderPresent(renderer);

	while (intro == true)
	{
		

		
	}

	return intro;
}


void Game::CleanUp() {
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}