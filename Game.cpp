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
	texture = SDL_CreateTextureFromSurface(renderer, title);
	return true;
}

bool Game::introScreen() {
	//Fill background
	SDL_SetRenderDrawColor(renderer, 0xBB, 0xFF, 0xFF, 1);
	SDL_RenderFillRect(renderer, NULL);

	//Create rectangles
	SDL_Rect cardRects[13];
	SDL_Rect leftRect[3];
	SDL_Rect rightRect[3];

	for (int i = 0; i < 13; i++)
	{
		cardRects[i] = {120 * i,0 , 120 ,235 };
	}

	for (int i = 0; i < 3; i++)
	{

		leftRect[i] = { -WINDOW_WIDTH, 100 + i * 50, WINDOW_WIDTH, 20 };
		rightRect[i] = { WINDOW_WIDTH, 400 + i * 50, WINDOW_WIDTH, 20 };

	}

	//Animation, I guess
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 1);
	for (int i = 0; i < WINDOW_WIDTH; i++)
	{
		titleCard.x = i;
		for (int i = 0; i < 3; i++)
		{
			leftRect[i].x++;
			rightRect[i].x--;

			SDL_RenderDrawRect(renderer, &leftRect[i]);
			SDL_RenderDrawRect(renderer, &rightRect[i]);
		}

		if (i == titleCard.w * 1 - 50)
		{
			SDL_RenderCopy(renderer, texture, &cardRects[0], &titleCard);
		}

		if (i == titleCard.w * 2 - 50)
		{
			SDL_RenderCopy(renderer, texture, &cardRects[1], &titleCard);
		}

		if (i == titleCard.w * 3 - 50)
		{
			SDL_RenderCopy(renderer, texture, &cardRects[2], &titleCard);
		}

		if (i == titleCard.w * 4 - 50)
		{
			SDL_RenderCopy(renderer, texture, &cardRects[3], &titleCard);
		}

		if (i == titleCard.w * 5 - 50)
		{
			SDL_RenderCopy(renderer, texture, &cardRects[4], &titleCard);
		}

		if (i == titleCard.w * 6 - 50)
		{
			SDL_RenderCopy(renderer, texture, &cardRects[5], &titleCard);
		}

		if (i == titleCard.w * 7 - 50)
		{
			SDL_RenderCopy(renderer, texture, &cardRects[6], &titleCard);
		}

		if (i == titleCard.w * 8 - 50)
		{
			SDL_RenderCopy(renderer, texture, &cardRects[7], &titleCard);
		}

		if (i == titleCard.w * 9 - 50)
		{
			SDL_RenderCopy(renderer, texture, &cardRects[8], &titleCard);
		}

		if (i == titleCard.w *10 - 50)
		{
			SDL_RenderCopy(renderer, texture, &cardRects[9], &titleCard);
		}

		if (i == titleCard.w *11 - 50)
		{
			SDL_RenderCopy(renderer, texture, &cardRects[10], &titleCard);
		}

		if (i == titleCard.w *12 - 50)
		{
			SDL_RenderCopy(renderer, texture, &cardRects[11], &titleCard);
		}

		if (i == titleCard.w*13 - 50)
		{
			SDL_RenderCopy(renderer, texture, &cardRects[12], &titleCard);
		}

		SDL_RenderPresent(renderer);
	}

	//SDL_RenderCopy(renderer, texture, NULL, &titleCard);
	SDL_RenderPresent(renderer);
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