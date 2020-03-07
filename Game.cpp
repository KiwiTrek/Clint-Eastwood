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
	if (window == NULL) {
		std::cout << "Window: Could not initialize. Error: " << SDL_GetError() << std::endl;
		return false;
	}

	//Surface
	windowSurface = SDL_GetWindowSurface(window); 
	if (windowSurface == NULL) {
		std::cout << "Window Surface: Could not initialize. Error: " << SDL_GetError() << std::endl;
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

	//////////////
	//Load media//
	//////////////

	//Title Screen
	title = IMG_Load("Resources/VolleyMasters.png");
	truth = IMG_Load("Resources/Truth.png");
	enterToStart = IMG_Load("Resources/EnterToStart.png");
	logo = IMG_Load("Resources/logo.png");

	texture = SDL_CreateTextureFromSurface(renderer, title);
	textureTruth = SDL_CreateTextureFromSurface(renderer, truth);
	textureEnterToStart = SDL_CreateTextureFromSurface(renderer, enterToStart);
	textureLogo = SDL_CreateTextureFromSurface(renderer, logo);

	test.setX(100);
	test.setY(100);
	test.setWidth(100);
	test.setHeight(100);
	test.setSpeedX(0);
	test.setSpeedY(0);

	//Game
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

	/*Puede que esto cause problemas con input, ya que como no 
	puede llegar a game.Input nunca debido a como está hecho el loop del main,
	no puede volverse false. Básicamente,
	Ahora mismo esto es un loop infinito.

	Needs checkup*/
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
		intro = false;	//Comando temporal para romper el loop.
						//Debería hacerlo un input.
	}



	return true;
}

bool Game::Input(){
	return false;
}


bool Game::Logic() {
	test.physics(test, WINDOW_WIDTH, WINDOW_HEIGHT);
	return false;
}


void Game::Render()
{
	//Temporal BG
	SDL_SetRenderDrawColor(renderer, 0xBB, 0xFF, 0xFF, 1);
	SDL_RenderFillRect(renderer, NULL);
	
	//Temporal Ground
	SDL_Rect ground = { 0,(WINDOW_HEIGHT * 3) / 4,WINDOW_WIDTH,WINDOW_HEIGHT / 4 };
	SDL_SetRenderDrawColor(renderer, 0x62, 0x4A, 0x2E, 1);
	SDL_RenderFillRect(renderer,&ground);

	//Temporal Balls
	SDL_Rect ball1;
	ball1.h = 100;
	ball1.w = 100;
	ball1.x = 200;
	ball1.y = 200;
	test.getRect(&ball1.x, &ball1.y, &ball1.w, &ball1.h);
	SDL_Rect ball2;
	test.getRect(&ball2.x, &ball2.y, &ball2.w, &ball2.h);
	ball2.x += WINDOW_WIDTH / 4;
	SDL_SetRenderDrawColor(renderer, 0xFE, 0xFE, 0xFE, 1);
	SDL_RenderFillRect(renderer, &ball1);
	SDL_RenderFillRect(renderer, &ball2);

	SDL_RenderPresent(renderer);
}


void Game::CleanUp() {
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}