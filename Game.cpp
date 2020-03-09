#include "Game.h"
#include "Entity.h"

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
	ball.setSpeedY(-200);  //Lo he convertido a -200 para que parezca mas floaty al empezar las rondas -Luce
	ball.setID(ID_BALL);
	ballSur = IMG_Load("Resources/Sprites/VolleyBall.png");
	ballTxt = SDL_CreateTextureFromSurface(renderer,ballSur);

		//Player1
	player1.setHeight(200);
	player1.setX(WINDOW_WIDTH / 4);
	player1.setY((WINDOW_HEIGHT * 3) / 4 - player1.getHeight());
	player1.setWidth(200);
	player1.setID(ID_PLAYER);
	player1sur = IMG_Load("Resources/Sprites/Player1.png");
	player1txt = SDL_CreateTextureFromSurface(renderer, player1sur);
	setAnim(player1animations);

		//Player2
	player2.setWidth(200);
	player2.setHeight(200);
	player2.setX((WINDOW_WIDTH * 3) / 4 - player2.getWidth());
	player2.setY((WINDOW_HEIGHT * 3) / 4 - player2.getHeight());
	player2.setID(ID_PLAYER);
	player2sur = IMG_Load("Resources/Sprites/Player2.png");
	player2txt = SDL_CreateTextureFromSurface(renderer, player2sur);
	setAnim(player2animations);

		//Net
	net.setWidth(25);
	net.setX((WINDOW_WIDTH / 2)-((net.getWidth())/2));
	net.setY(((WINDOW_HEIGHT * 3) / 7) - 10);
	net.setHeight(WINDOW_HEIGHT / 3);
	net.setID(ID_NET);
	netSur = IMG_Load("Resources/Sprites/VolleyPole.png");
	netTxt = SDL_CreateTextureFromSurface(renderer, netSur);

	bgSurface = IMG_Load("Resources/Sprites/Background.jpg");
	bgTxt = SDL_CreateTextureFromSurface(renderer, bgSurface);

	//Game texts

	sGetReady = IMG_Load("Resources/GetReady.png");
	sPlayBall = IMG_Load("Resources/PlayBall.png");
	sGame = IMG_Load("Resources/Game.png");
	sPoint = IMG_Load("Resources/Point.png");

	tGetReady = SDL_CreateTextureFromSurface(renderer, sGetReady);
	tPlayBall = SDL_CreateTextureFromSurface(renderer, sPlayBall);
	tGame = SDL_CreateTextureFromSurface(renderer, sGame);
	tPoint = SDL_CreateTextureFromSurface(renderer, sPoint);

	return true;
}
void Game::setAnim(SDL_Rect* anim) {
	//IDLE
	anim[0].x = 33;
	anim[0].y = 3;
	anim[0].w = 62;
	anim[0].h = 115;

	anim[1].x = 114;
	anim[1].y = 3;
	anim[1].w = 62;
	anim[1].h = 115;

	anim[2].x = 195;
	anim[2].y = 3;
	anim[2].w = 62;
	anim[2].h = 115;
	
	anim[3].x = 276;
	anim[3].y = 3;
	anim[3].w = 62;
	anim[3].h = 115;

	anim[4].x = 356;
	anim[4].y = 3;
	anim[4].w = 62;
	anim[4].h = 115;

	anim[5].x = 433;
	anim[5].y = 3;
	anim[5].w = 60;
	anim[5].h = 115;


	//RUNNING
	anim[6].x = 40;
	anim[6].y = 124;
	anim[6].w = 60;
	anim[6].h = 113;

	anim[7].x = 102;
	anim[7].y = 124;
	anim[7].w = 73;
	anim[7].h = 113;

	anim[8].x = 178;
	anim[8].y = 124;
	anim[8].w = 81;
	anim[8].h = 113;

	anim[9].x = 274;
	anim[9].y = 124;
	anim[9].w = 64;
	anim[9].h = 113;

	anim[10].x = 350;
	anim[10].y = 124;
	anim[10].w = 66;
	anim[10].h = 113;

	anim[11].x = 425;
	anim[11].y = 124;
	anim[11].w = 71;
	anim[11].h = 113;

	//JUMPING
	anim[12].x = 39;
	anim[12].y = 289;
	anim[12].w = 63;
	anim[12].h = 108;

	anim[13].x = 108;
	anim[13].y = 274;
	anim[13].w = 57;
	anim[13].h = 115;

	anim[14].x = 181;
	anim[14].y = 248;
	anim[14].w = 72;
	anim[14].h = 100;

	anim[15].x = 260;
	anim[15].y = 262;
	anim[15].w = 74;
	anim[15].h = 110;

	anim[16].x = 342;
	anim[16].y = 280;
	anim[16].w = 68;
	anim[16].h = 112;

	anim[17].x = 423;
	anim[17].y = 290;
	anim[17].w = 63;
	anim[17].h = 107;

	//QTE
	anim[18].x = 8;
	anim[18].y = 408;
	anim[18].w = 77;
	anim[18].h = 110;

	anim[19].x = 103;
	anim[19].y = 408;
	anim[19].w = 70;
	anim[19].h = 110;

	anim[20].x = 179;
	anim[20].y = 408;
	anim[20].w = 85;
	anim[20].h = 110;

	//Loss
	anim[21].x = 276;
	anim[21].y = 408;
	anim[21].w = 66;
	anim[21].h = 103;

	anim[22].x = 366;
	anim[22].y = 408;
	anim[22].w = 66;
	anim[22].h = 103;

	anim[23].x = 449;
	anim[23].y = 408;
	anim[23].w = 66;
	anim[23].h = 103;
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
    player1.setSpeedX(0);
    player2.setSpeedX(0);
	if (keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN)	return true;
	if (keys[SDL_SCANCODE_A] == KEY_REPEAT) {
        player1.setSpeedX(-150);
		player1.setAnimationState(1);
	}
	if (keys[SDL_SCANCODE_D] == KEY_REPEAT) {
        player1.setSpeedX(200);
		player1.setAnimationState(2);
	}
	if (keys[SDL_SCANCODE_W] == KEY_DOWN) {
        player1.setSpeedY(-400);
		player1.setAnimationState(3);
	}
	
	if (keys[SDL_SCANCODE_LEFT] == KEY_REPEAT) {
        player2.setSpeedX(-150);
		player2.setAnimationState(1);
	}
	if (keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT) {
        player2.setSpeedX(200);
		player2.setAnimationState(2);
	}
	if (keys[SDL_SCANCODE_UP] == KEY_DOWN) {
        player2.setSpeedY(-400);
		player2.setAnimationState(3);
	}

	if (keys[SDL_SCANCODE_RETURN] == KEY_DOWN  && intro == true)
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


void Game::Scoreboard()
{
	//Creates numbers, couldn't simplify sry
	numbers[0] = IMG_Load("Resources/Numbers/0.png");
	numbers[1] = IMG_Load("Resources/Numbers/1.png");
	numbers[2] = IMG_Load("Resources/Numbers/2.png");
	numbers[3] = IMG_Load("Resources/Numbers/3.png");
	numbers[4] = IMG_Load("Resources/Numbers/4.png");
	numbers[5] = IMG_Load("Resources/Numbers/5.png");
	numbers[6] = IMG_Load("Resources/Numbers/6.png");
	numbers[7] = IMG_Load("Resources/Numbers/7.png");
	numbers[8] = IMG_Load("Resources/Numbers/8.png");
	numbers[9] = IMG_Load("Resources/Numbers/9.png");

	//Could simplify this, tho :3
	for (int i = 0; i < 10; i++)
	{
		tNumbers[i] = SDL_CreateTextureFromSurface(renderer, numbers[i]);
	}
	
	if (ball.getY() >=  + WINDOW_HEIGHT * 3 / 4 - ball.getHeight())
	{
		pointS1 = true;


		//Point for player1
		if (ball.getX() > WINDOW_WIDTH / 2)
		{
			ball.setSpeedX(-200);
			ball.setSpeedY(-200);
			score1[1]++;

			if (score1[1] > 9)
			{
				score1[0]++;
				score1[1] = 0;
			}
			if (score1[0] > 9)
			{
				score1[0] = 9;
				score1[1] = 9;
			}
		}
		//Point for player2
		if (ball.getX() < WINDOW_WIDTH / 2)
		{
			ball.setSpeedX(200);
			ball.setSpeedY(-200);
			score2[1]++;

			if (score2[1] > 9)
			{
				score2[0]++;
				score2[1] = 0;
			}
			if (score2[0] > 9)
			{
				score2[0] = 9;
				score2[1] = 9;
			}
		}	
	}	
}

bool Game::Logic() {
	ball.physics();
    player1.physics();
    player2.physics();
    net.physics();
	ball.collisions(net);
    ball.collisions(player1);
    ball.collisions(player2);
    player1.collisions(net);
    player2.collisions(net);
	return false;
}


void Game::Render()
{
	SDL_RenderClear(renderer);
	//Background
	SDL_RenderCopy(renderer, bgTxt, NULL, NULL);
	
	//Ground Measurements
	//SDL_Rect ground = { 0,(WINDOW_HEIGHT * 3) / 4,WINDOW_WIDTH,WINDOW_HEIGHT / 4 };

	//Ball
	SDL_Rect ball_Rect;
	ball.getRect(&ball_Rect.x, &ball_Rect.y, &ball_Rect.w, &ball_Rect.h);
	SDL_RenderCopy(renderer, ballTxt, NULL, &ball_Rect);

	//Pole
	SDL_Rect net_Rect;
	net.getRect(&net_Rect.x, &net_Rect.y, &net_Rect.w, &net_Rect.h);
	SDL_RenderCopy(renderer, netTxt, NULL, &net_Rect);

	//Player1
	SDL_Rect player1rect;
	player1.getRect(&player1rect.x, &player1rect.y, &player1rect.w, &player1rect.h);
	SDL_RenderCopy(renderer, player1txt, &player1animations[0] ,&player1rect);

	//Player2
	SDL_Rect player2rect;
	player2.getRect(&player2rect.x, &player2rect.y, &player2rect.w, &player2rect.h);
	SDL_RenderCopy(renderer, player2txt, &player2animations[0], &player2rect);

	//Scoreboard
	//Player 1
	for (int i = 0; i <= 9; i++)
	{
		if (score1[0] == i)
		{
			SDL_RenderCopy(renderer, tNumbers[i], NULL, &numbersCard1);
		}

		for (int j = 0; j <= 9; j++)
		{
			if (score1[1] == j)
			{
				SDL_RenderCopy(renderer, tNumbers[j], NULL, &numbersCard2);
			}
		}
	}
	//Player 2
	for (int i = 0; i <= 9; i++)
	{
		if (score2[0] == i)
		{
			SDL_RenderCopy(renderer, tNumbers[i], NULL, &numbersCard3);
		}

		for (int j = 0; j <= 9; j++)
		{
			if (score2[1] == j)
			{
				SDL_RenderCopy(renderer, tNumbers[j], NULL, &numbersCard4);
			}
		}
	}

	//After getting a point (Part of ball repositioning is also done here, to avoid certain weird shit)
	if (pointS3)
	{
		ball.setX(WINDOW_WIDTH / 2 -ball.getWidth()/2);
		ball.setY(200);
		SDL_RenderCopy(renderer, tPlayBall, NULL, &multiCard);
		playBall = Mix_LoadWAV("Resources/announcer_play_ball.wav");
		Mix_PlayChannel(-1, playBall, 0);
		SDL_RenderPresent(renderer);
		SDL_Delay(1300);
		pointS3 = false;
	}
	if (pointS2)
	{
		ball.setX(WINDOW_WIDTH / 2 - ball.getWidth()/2);
		ball.setY(200);
		SDL_RenderCopy(renderer, tGetReady, NULL, &multiCard);
		getReady = Mix_LoadWAV("Resources/announcer_get_ready.wav");
		Mix_PlayChannel(-1, getReady, 0);
		SDL_RenderPresent(renderer);
		SDL_Delay(1200);
		pointS2 = false;
		pointS3 = true;
	}
	if (pointS1)
	{
		ball.setX(WINDOW_WIDTH / 2 - ball.getWidth()/2);
		ball.setY(200);
		SDL_RenderCopy(renderer, tPoint, NULL, &multiCard);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
		pointS1 = false;
		pointS2 = true;
	}		

	SDL_RenderPresent(renderer);
}


void Game::CleanUp() {
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}