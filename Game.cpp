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
	player1Controls = IMG_Load("Resources/Player1Controls.png");
	player2Controls = IMG_Load("Resources/Player2Controls.png");
	PE2Q = IMG_Load("Resources/PressEscToQuit.png");

	texture = SDL_CreateTextureFromSurface(renderer, title);
	textureTruth = SDL_CreateTextureFromSurface(renderer, truth);
	textureEnterToStart = SDL_CreateTextureFromSurface(renderer, enterToStart);
	textureLogo = SDL_CreateTextureFromSurface(renderer, logo);
	tP1C = SDL_CreateTextureFromSurface(renderer, player1Controls);
	tP2C = SDL_CreateTextureFromSurface(renderer, player2Controls);
	tPE2Q = SDL_CreateTextureFromSurface(renderer, PE2Q);

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
	player1.setWidth(100);
	player1.setID(ID_PLAYER);

	player1surIdle = IMG_Load("Resources/Sprites/Player1Idle.png");
	player1txtIdle = SDL_CreateTextureFromSurface(renderer, player1surIdle);

	player1surJump = IMG_Load("Resources/Sprites/Player1Jump.png");
	player1txtJump = SDL_CreateTextureFromSurface(renderer, player1surJump);

	player1surLeft = IMG_Load("Resources/Sprites/Player1Left.png");
	player1txtLeft = SDL_CreateTextureFromSurface(renderer, player1surLeft);

	player1surRight = IMG_Load("Resources/Sprites/Player1Right.png");
	player1txtRight = SDL_CreateTextureFromSurface(renderer, player1surRight);


		//Player2
	player2.setWidth(100);
	player2.setHeight(200);
	player2.setX((WINDOW_WIDTH * 3) / 4 - player2.getWidth());
	player2.setY((WINDOW_HEIGHT * 3) / 4 - player2.getHeight());
	player2.setID(ID_PLAYER);

	player2surIdle = IMG_Load("Resources/Sprites/Player2Idle.png");
	player2txtIdle = SDL_CreateTextureFromSurface(renderer, player2surIdle);

	player2surJump = IMG_Load("Resources/Sprites/Player2Jump.png");
	player2txtJump = SDL_CreateTextureFromSurface(renderer, player2surJump);

	player2surLeft = IMG_Load("Resources/Sprites/Player2Left.png");
	player2txtLeft = SDL_CreateTextureFromSurface(renderer, player2surLeft);

	player2surRight = IMG_Load("Resources/Sprites/Player2Right.png");
	player2txtRight = SDL_CreateTextureFromSurface(renderer, player2surRight);


		//Net
	net.setWidth(10);
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
	sP1Wins = IMG_Load("Resources/Player1Wins.png");
	sP2Wins = IMG_Load("Resources/Player2Wins.png");

	tGetReady = SDL_CreateTextureFromSurface(renderer, sGetReady);
	tPlayBall = SDL_CreateTextureFromSurface(renderer, sPlayBall);
	tGame = SDL_CreateTextureFromSurface(renderer, sGame);
	tPoint = SDL_CreateTextureFromSurface(renderer, sPoint);
	tP1Wins = SDL_CreateTextureFromSurface(renderer, sP1Wins);
	tP2Wins = SDL_CreateTextureFromSurface(renderer, sP2Wins);

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
    player1.setSpeedX(0);
	if (player1.getY() == (WINDOW_HEIGHT * 3) / 4 - player1.getHeight()) { player1.setAnimationState(0); }
    player2.setSpeedX(0);
	if (player2.getY() == (WINDOW_HEIGHT * 3) / 4 - player2.getHeight()) { player2.setAnimationState(0); }
	if (keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN)	return true;
	if (keys[SDL_SCANCODE_A] == KEY_REPEAT) {
        player1.setSpeedX(-150);
		player1.setAnimationState(1);
	}
	if (keys[SDL_SCANCODE_D] == KEY_REPEAT) {
        player1.setSpeedX(200);
		player1.setAnimationState(2);
	}
	if (keys[SDL_SCANCODE_W] == KEY_DOWN && player1.getY() == (WINDOW_HEIGHT * 3) / 4 - player1.getHeight()) {
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
	if (keys[SDL_SCANCODE_UP] == KEY_DOWN && player2.getY() == (WINDOW_HEIGHT * 3) / 4 - player2.getHeight()) {
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
		gameMusic = Mix_LoadMUS("Resources/DeathByGlamour.ogg");
		Mix_PlayMusic(gameMusic, -1);
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
	Mix_PlayMusic(introMusic, 0);
	
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
	SDL_RenderCopy(renderer, tP1C, NULL, &P1CCard);
	SDL_RenderCopy(renderer, tP2C, NULL, &P2CCard);
	SDL_RenderCopy(renderer, tPE2Q, NULL, &PE2QCard);
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
		points = 1;


		//Point for player1
		if (ball.getX() > WINDOW_WIDTH / 2)
		{
			ball.setSpeedX(200);
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
			ball.setSpeedX(-200);
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

bool Game::winCondition()
{
	int trueScore1 = score1[0] * 10 + score1[1];
	int trueScore2 = score2[0] * 10 + score2[1];

	if (trueScore1 >= 11 && trueScore1 - trueScore2 > 1)
	{
		points = 0;
		SDL_RenderCopy(renderer, tGame, NULL, &multiCard);
		SDL_RenderCopy(renderer, tP1Wins, NULL, &playerWins);
		game = Mix_LoadWAV("Resources/announcer_game.wav");
		Mix_PlayChannel(-1, game, 0);
		SDL_RenderPresent(renderer);
		SDL_Delay(2000);
		return true;
	}
	if (trueScore2 >= 11 && trueScore2 - trueScore1 > 1)
	{
		points = 0;
		SDL_RenderCopy(renderer, tGame, NULL, &multiCard);
		SDL_RenderCopy(renderer, tP2Wins, NULL, &playerWins);
		game = Mix_LoadWAV("Resources/announcer_game.wav");
		Mix_PlayChannel(-1, game, 0);
		SDL_RenderPresent(renderer);
		SDL_Delay(2000);
		return true;
	}
	return false;
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
	switch (player1.getAnimationState()) {
	case 0:
		SDL_RenderCopy(renderer, player1txtIdle, NULL, &player1rect);
		break;
	case 1:
		SDL_RenderCopy(renderer, player1txtLeft, NULL, &player1rect);
		break;
	case 2:
		SDL_RenderCopy(renderer, player1txtRight, NULL, &player1rect);
		break;
	case 3:
		SDL_RenderCopy(renderer, player1txtJump, NULL, &player1rect);
		break;
	default:
		break;
	}

	//Player2
	SDL_Rect player2rect;
	player2.getRect(&player2rect.x, &player2rect.y, &player2rect.w, &player2rect.h);
	switch (player2.getAnimationState()) {
	case 0:
		SDL_RenderCopy(renderer, player2txtIdle, NULL, &player2rect);
		break;
	case 1:
		SDL_RenderCopy(renderer, player2txtLeft, NULL, &player2rect);
		break;
	case 2:
		SDL_RenderCopy(renderer, player2txtRight, NULL, &player2rect);
		break;
	case 3:
		SDL_RenderCopy(renderer, player2txtJump, NULL, &player2rect);
		break;
	default:
		break;
	}

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

	win = winCondition();

	if (points == 3)
	{
		ball.setX(WINDOW_WIDTH / 2 -ball.getWidth()/2);
		ball.setY(200);
		player1.setX(WINDOW_WIDTH / 4);
		player2.setX((WINDOW_WIDTH * 3 / 4) - player2.getWidth());
		player1.setY((WINDOW_HEIGHT * 3 / 4) - player1.getHeight());
		player2.setY((WINDOW_HEIGHT * 3 / 4) - player2.getHeight());
		SDL_RenderCopy(renderer, tPlayBall, NULL, &multiCard);
		playBall = Mix_LoadWAV("Resources/announcer_play_ball.wav");
		Mix_PlayChannel(-1, playBall, 0);
		SDL_RenderPresent(renderer);
		SDL_Delay(1300);
		points = 0;
	}
	if (points == 2)
	{
		ball.setX(WINDOW_WIDTH / 2 - ball.getWidth()/2);
		ball.setY(200);
		player1.setX(WINDOW_WIDTH / 4);
		player2.setX((WINDOW_WIDTH * 3 / 4) - player2.getWidth());
		player1.setY((WINDOW_HEIGHT * 3 / 4) - player1.getHeight());
		player2.setY((WINDOW_HEIGHT * 3 / 4) - player2.getHeight());
		SDL_RenderCopy(renderer, tGetReady, NULL, &multiCard);
		getReady = Mix_LoadWAV("Resources/announcer_get_ready.wav");
		Mix_PlayChannel(-1, getReady, 0);
		SDL_RenderPresent(renderer);
		SDL_Delay(1200);
		points++;
	}
	if (points == 1)
	{
		ball.setX(WINDOW_WIDTH / 2 - ball.getWidth()/2);
		ball.setY(200);
		player1.setX(WINDOW_WIDTH / 4);
		player2.setX((WINDOW_WIDTH * 3 / 4) - player2.getWidth());
		player1.setY((WINDOW_HEIGHT * 3 / 4) - player1.getHeight());
		player2.setY((WINDOW_HEIGHT * 3 / 4) - player2.getHeight());
		SDL_RenderCopy(renderer, tPoint, NULL, &multiCard);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
		points++;
	}		

	SDL_RenderPresent(renderer);
}


void Game::CleanUp() {
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}