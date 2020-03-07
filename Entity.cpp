/*Aquí irían las declaraciones de las funciones de entity*/
#include "Entity.h"

Entity::Entity() {};

bool Entity::IsAlive() { return is_alive; };

int Entity::getX() { return x; };
int Entity::getY() { return y; };
int Entity::getWidth() { return width; };
int Entity::getHeight() { return height; };
int Entity::getSpeedX() { return speedX; };
int Entity::getSpeedY() { return speedY; };

void Entity::setX(int X) { x = X; };
void Entity::setY(int Y) { y = Y; };
void Entity::setWidth(int WIDTH) { width = WIDTH; };
void Entity::setHeight(int HEIGHT) { height = HEIGHT; };
void Entity::setSpeedX(int SPEEDX) { speedX = SPEEDX; };
void Entity::setSpeedY(int SPEEDY) { speedY = SPEEDY; };

void Entity::physics(Entity &e, int WW, int WH) {
	const float gravity = 600.0f;				// pixels / second^2
	const float deltaTime = 1.0f / 60.0f;		// More or less 60 frames per second
	//------------------------------------------------------------------------------GRAVITY
	e.setX(e.getX() + e.getSpeedX() * deltaTime);
	e.setY(e.getY() + e.getSpeedY() * deltaTime + gravity * deltaTime * deltaTime);
	e.setSpeedY(e.getSpeedY() + gravity * deltaTime);

	//------------------------------------------------------------------------------BORDERS OF SCREEN
	if ((e.getX() + e.getWidth() - WW) >= 0) {										//Right border
		e.setSpeedX(-e.getSpeedX());
		e.setX(WW - e.getWidth());
	}
	if (e.getX() <= 0) {															//Left border
		e.setSpeedX(-e.getSpeedX());
		e.setX(0);
	}
	if (e.getY() >= (WH * 3) / 4 - e.getHeight()) {
		e.setY((WH * 3) / 4 - e.getHeight());
	}
}

void Entity::getRect(int* x, int* y, int* width, int* height) {
	*x = getX();
	*y = getY();
	*width = getWidth();
	*height = getHeight();
};