#pragma once
//Aquí solo se declara la clase Entity con todas sus funciones y variables
/*Si queréis hacer más clases, creais un header con declaraciones y luego un cpp
con las funciones definidas (como con el Game.h y el Game.cpp)*/
//No se hacen #include de game. Solo se declara la clase.
class Entity {
public:
	Entity();
	bool IsAlive();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	int getSpeedX();
	int getSpeedY();
	void setX(int X);
	void setY(int Y);
	void setWidth(int WIDTH);
	void setHeight(int HEIGHT);
	void setSpeedX(int SPEEDX);
	void setSpeedY(int SPEEDY);
private:
	bool is_alive = false;
	int x;
	int y;
	int width;
	int height;
	int speedX;
	int speedY;
};