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

	//Game

		//Ball
	ball.setX(WINDOW_WIDTH / 2);
	ball.setY(100);
	ball.setWidth(50);
	ball.setHeight(50);
	ball.setSpeedX(200);
	ball.setSpeedY(200);
	ball.setID(ID_BALL);

		//Player1
	player1.setX(WINDOW_WIDTH / 4);
	player1.setY(WINDOW_HEIGHT / 2);
	player1.setWidth(50);
	player1.setHeight(100);
	player1.setID(ID_PLAYER);

		//Player2
	player2.setX(WINDOW_WIDTH / 4);
	player2.setY(WINDOW_HEIGHT / 2);
	player2.setWidth(50);
	player2.setHeight(100);
	player2.setID(ID_PLAYER);

		//Net
	net.setWidth(25);
	net.setX((WINDOW_WIDTH / 2)-(net.getWidth()/2));
	net.setY((WINDOW_HEIGHT * 3) / 2);
	net.setHeight(WINDOW_HEIGHT / 4);
	net.setID(ID_NET);



	return true;
}


bool Game::Input() {

	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)	return false;
	}

	SDL_PumpEvents();
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < 256; ++i)
	{
		if (keyboard[i])
			keys[i] = (keys[i] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
		else
			keys[i] = (keys[i] == KEY_REPEAT || keys[i] == KEY_DOWN) ? KEY_UP : KEY_IDLE;
	}

	return true;
}
bool Game::Update()
{
	//Read Input
	if (!Input())	return true;

	//Process Input
	int fx = 0, fy = 0;
	if (keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN)	return true;
	if (keys[SDL_SCANCODE_UP] == KEY_REPEAT)	fy -= 1;
	if (keys[SDL_SCANCODE_DOWN] == KEY_REPEAT)	fy += 1;
	if (keys[SDL_SCANCODE_LEFT] == KEY_REPEAT)	fx -= 1;
	if (keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT)	fx += 1;
	if (keys[SDL_SCANCODE_RETURN] == KEY_DOWN  && intro== true)
	{
		SDL_RenderPresent(renderer);
		Mix_FreeMusic(introMusic);
		ohYes = Mix_LoadWAV("Resources/ohyes.wav");
		Mix_PlayChannel(-1, ohYes, 0);
		SDL_Delay(3000);
		Mix_FreeChunk(ohYes);
		intro = false;
	}
		

	return false;
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
	SDL_RenderCopy(renderer, textureEnterToStart, NULL, &enterToStartCard);
	SDL_RenderPresent(renderer);


	return true;
}




bool Game::Logic() {
	ball.physics(WINDOW_WIDTH, WINDOW_HEIGHT);
	//ball.collisions(ball2, WINDOW_WIDTH, WINDOW_HEIGHT);
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
	
	SDL_Rect ball_Rect;
	ball.getRect(&ball_Rect.x, &ball_Rect.y, &ball_Rect.w, &ball_Rect.h);
	SDL_Rect ball2_Rect;
	//ball2.getRect(&ball2_Rect.x, &ball2_Rect.y, &ball2_Rect.w, &ball2_Rect.h);
	
	SDL_SetRenderDrawColor(renderer, 0xFE, 0xFE, 0xFE, 1);
	SDL_RenderFillRect(renderer, &ball_Rect);
	SDL_RenderFillRect(renderer, &ball2_Rect);

	SDL_RenderPresent(renderer);
}


void Game::CleanUp() {
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}