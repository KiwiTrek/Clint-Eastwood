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
	int getID();
	void setX(int X);
	void setY(int Y);
	void setWidth(int WIDTH);
	void setHeight(int HEIGHT);
	void setSpeedX(int SPEEDX);
	void setSpeedY(int SPEEDY);
	void setID(int id);
	void physics(int WW, int WH);
	void collisions(Entity& e, int WW, int WH);
	void getRect(int* x, int* y, int* width, int* height);

	float sqrt(float X);
	float ballCenterX();
	float ballCenterY();
private:
	bool is_alive = false;
	int x = 0;
	int y = 0;
	int width = 1;
	int height = 1;
	int speedX = 1;
	int speedY = 1;
	int ID = 0;
};