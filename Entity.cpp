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

float Entity::CenterX() {
	float centerX = getX() + (getWidth()/2);
	return centerX;
}

float Entity::CenterY() {
	float centerY = getY() + (getHeight()/2);
	return centerY;
}

double Entity::weight() {
    int id = getID();
    if (id == 0) { //player
        return 5;
    }
    else if (id == 1) { //ball
        return 1.25;
    }
    else if (id == 2) { //net
        return 0.0625;
    }
}

void Entity::physics() {
	const float gravity = 600.0f;				// pixels / second^2
	const float deltaTime = 1.0f / 60.0f;		// More or less 60 frames per second
	//------------------------------------------------------------------------------GRAVITY
    //x += dx * speedX;
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
	int w1 = getWidth();
	int h1 = getHeight();
	int x2 = e.getX();
	int y2 = e.getY();
	int vx2 = e.getSpeedX();
	int vy2 = e.getSpeedY();
	int w2 = e.getWidth();
	int h2 = e.getHeight();
	int W = weight();
	float incrementX = (e.CenterX() - CenterX());
	float incrementY = (e.CenterY() - CenterY());
	bool isXP = (incrementX > 0) ? true : false;
	bool isYP = (incrementY > 0) ? true : false;
	bool isVXP = ((vx1 - vx2) > 0) ? true : false;
	bool isVYP = ((vy1 - vy2) > 0) ? true : false;


	if (ID1 == 1 && ID2 == 0) {																			//If the first entity is a ball and the second is a player
        if (sqrt(incrementX * incrementX + incrementY * incrementY) <= 125/*(getWidth()/2 + e.getWidth()/2)*/) {
			if (isXP == false && !(vx1 > 0 && vx2 < 0)) {
                setSpeedX(vx1 < 0 ? -vx1 / W : vx1 * W);
                e.setSpeedX(vx2 < 0 ? vx2 * W : -vx2 / W);
            }
            else if (isXP == true && !(vx1 < 0 && vx2 > 0)) {
                setSpeedX(vx1 > 0 ? -vx1 / W : vx1 * W);
                e.setSpeedX(vx2 > 0 ? vx2 * W : -vx2 / W);
            }
            if (isYP == false && !(vy1 > 0 && vy2 < 0)) {
                setSpeedY(vy1 < 0 ? vy1 * W : -vy1 / W);
                e.setSpeedY(vy2 < 0 ? -vy2 / W : vy2 * W);
            }
            else if (isYP == true && !(vy1 < 0 && vy2 > 0)) {
                setSpeedY(vy1 > 0 ? -vy1 / W : vy1 * W);
                e.setSpeedY(vy2 > 0 ? vy2 * W : -vy2 / W);
            }
        }
	}
    else if (ID1 == 1 && ID2 == 2) {																	//If the first entity is a ball and the second is a net
		if (isXP == false && x1 <= (x2 + w2) && (y1 + h1) >= y2) {
			setX(x2 + w2);
			setSpeedX(vx1 < 0 ? -vx1 / W : vx1 * W);
		}
		else if ( isXP == true && (x1 + w1) >= x2 && (y1 + h1) >= y2) {
			setX(x2 - w1);
			setSpeedX(vx1 > 0 ? -vx1 / W : vx1 * W);
		}
    }
    else if (ID1 == 0 && ID2 == 2) {																	//If the first entity is a player and the second is a net
		if (isXP == false && x1 <= (x2 + w2)) {
			setX(x2 + w2);
		}
		else if (isXP == true && (x1 + w1) >= x2) {
			setX(x2 - w1);
		}
    }
}

void Entity::getRect(int* x, int* y, int* width, int* height) {
	*x = getX();
	*y = getY();
	*width = getWidth();
	*height = getHeight();
};