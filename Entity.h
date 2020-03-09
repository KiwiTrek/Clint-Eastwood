#pragma once
//Aquí solo se declara la clase Entity con todas sus funciones y variables
/*Si queréis hacer más clases, creais un header con declaraciones y luego un cpp
con las funciones definidas (como con el Game.h y el Game.cpp)*/
//No se hacen #include de game. Solo se declara la clase.
class Entity {
public:
	Entity();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	int getSpeedX();
	int getSpeedY();
	int getID();
	int getAnimationState();

	void setX(int X);
	void setY(int Y);
	void setWidth(int WIDTH);
	void setHeight(int HEIGHT);
	void setSpeedX(int SPEEDX);
	void setSpeedY(int SPEEDY);
	void setID(int id);
	void setAnimationState(int state_);

	void physics();
	void collisions(Entity& e);
	float sqrt(float X);
	float CenterX();
	float CenterY();
    double weight();

	void getRect(int* x, int* y, int* width, int* height);

private:
	int x = 0;
	int y = 0;
	int width = 1;
	int height = 1;
	int speedX = 1;
	int speedY = 1;
	int ID = 0;

	int animationState = 0;
	/*
	0 = IDLE
	1 = MOVING_LEFT
	2 = MOVING_RIGHT
	3 = JUMPING
	4 = QTE
	5 = LOSS
	*/
};