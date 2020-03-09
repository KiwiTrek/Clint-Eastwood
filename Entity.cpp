/*Aquí irían las declaraciones de las funciones de entity*/
#include "Entity.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960

Entity::Entity() {};

int Entity::getX() { return x; };
int Entity::getY() { return y; };
int Entity::getWidth() { return width; };
int Entity::getHeight() { return height; };
int Entity::getSpeedX() { return speedX; };
int Entity::getSpeedY() { return speedY; };
int Entity::getID() { return ID; };
int Entity::getAnimationState() { return animationState; };

void Entity::setX(int X) { x = X; };
void Entity::setY(int Y) { y = Y; };
void Entity::setWidth(int WIDTH) { width = WIDTH; };
void Entity::setHeight(int HEIGHT) { height = HEIGHT; };
void Entity::setSpeedX(int SPEEDX) { speedX = SPEEDX; };
void Entity::setSpeedY(int SPEEDY) { speedY = SPEEDY; };
void Entity::setID(int id) { ID = id; };
void Entity::setAnimationState(int state_) { animationState = state_; };

float Entity::sqrt(float X) {
	float number;
	float sqrt;
	sqrt = X / 2;
	number = 0;
	while (sqrt != number) {
		number = sqrt;
		sqrt = (X / number + number) / 2;
	}
	return sqrt;
}

float Entity::ballCenterX() {
	float centerX = getX() + (getWidth()/2);
	return centerX;
}

float Entity::ballCenterY() {
	float centerY = getY() + (getHeight()/2);
	return centerY;
}

double Entity::weight() {
    int id = getID();
    if (id == 0) {
        return 1.125;
    }
    else if (id == 1) {
        return 1.0625;
    }
    else if (id == 2) {
        return 69420;
    }
}

void Entity::physics() {
	const float gravity = 600.0f;				// pixels / second^2
	const float deltaTime = 1.0f / 60.0f;		// More or less 60 frames per second
	//------------------------------------------------------------------------------GRAVITY
	setX(getX() + getSpeedX() * deltaTime);
	setY(getY() + getSpeedY() * deltaTime + gravity * deltaTime * deltaTime);
	setSpeedY(getSpeedY() + gravity * deltaTime);

	//------------------------------------------------------------------------------BORDERS OF SCREEN
	if ((getX() + getWidth() - WINDOW_WIDTH) >= 0) {										//Right border
		setSpeedX(-getSpeedX());
		setX(WINDOW_WIDTH - getWidth());
	}
	if (getX() <= 0) {															//Left border
		setSpeedX(-getSpeedX());
		setX(0);
	}
	if (getY() >= (WINDOW_HEIGHT * 3) / 4 - getHeight()) {                                 //Ground
		setY((WINDOW_HEIGHT * 3) / 4 - getHeight());
	}
}
																				//////////////////////////////////////////////////////////////////////////////////////////////
																				// IF THERE ARE COLLISIONS AND A BALL IS INFLUENCED, THE BALL WILL BE THE CALLING OBJECT	//
void Entity::collisions(Entity& e) {					                    	// IF THERE ARE COLLISIONS AND A NET IS INFLUENCED, THE NET WILL BE THE SECOND OBJECT		//
	int ID1 = getID();															//////////////////////////////////////////////////////////////////////////////////////////////
	int ID2 = e.getID();
	int x1 = getX();
	int y1 = getY();
	int vx1 = getSpeedX();
	int vy1 = getSpeedY();
	int x2 = getX();
	int y2 = getY();
	int vx2 = e.getSpeedX();
	int vy2 = e.getSpeedY();
	float incrementX = (x2 + e.getWidth()/2) - ballCenterX();
	float incrementY = (y2 + e.getHeight()/2) - ballCenterY();
	bool isXP = (incrementX > 0) ? true : false;
	bool isYP = (incrementY > 0) ? true : false;
	bool isVXP = ((vx1 - vx2) > 0) ? true : false;
	bool isVYP = ((vy1 - vy2) > 0) ? true : false;

	if (sqrt(incrementX * incrementX + incrementY * incrementY) <= (getWidth()/4 + e.getWidth()/4)) {
		if (isXP == false) {
            if (!(vx1 > 0 && vx2 < 0)) {
                setSpeedX(vx1 < 0 ? -vx1 / weight() : vx1 * weight());
                e.setSpeedY(vx2 < 0 ? vx2 * e.weight() : -vx2 / e.weight());
            }
		}
		else if(isXP == true) {
            if (!(vx1 < 0 && vx2 > 0)) {
                setSpeedX(vx1 > 0 ? -vx1 / weight() : vx1 * weight());
                e.setSpeedX(vx2 > 0 ? vx2 * e.weight() : -vx2 / e.weight());
            }
		}

		if (isYP == false) {

		}
		else if(isYP == true) {

		}
	}
	if (ID1 == 1 && ID2 == 0) {																			//If the first entity is a ball and the second is a player
		if (vx1 > 0 && vx2 > 0) {

		}
	}
	else if (ID1 == 1 && ID2 == 2) {																	//If the first entity is a ball and the second is a net

	}
	else if (ID1 == 0 && ID2 == 2) {																	//If the first entity is a player and the second is a net

	}
}

void Entity::getRect(int* x, int* y, int* width, int* height) {
	*x = getX();
	*y = getY();
	*width = getWidth();
	*height = getHeight();
};