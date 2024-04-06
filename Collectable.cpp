#include "collectable.h"
#include "paddle.h"
#include "game.h"

//
//#include <cstdlib>
//#include <ctime>
//

collectable::collectable(point uprleft, int w, int h, game* r_pGame) :
	collidable(uprleft, width, height, pGame) {}

void collectable::collisionAction()
{
	doRandomAction();
}

collectable* collectable::getCollectable()
{
	return this;
}

void collectable::doRandomAction()
{
	//randomly select between power ups and downs and implement it.

}

void collectable::WindGlid()
{
	paddle* pad = pGame->getpaddle();
	int oldspeed = pad->getspeed();
	pad->setspeed(25);
	// apply duration
	pad->setspeed(oldspeed);
}
// powerdowns
void collectable::ReverseDirection()
{
	// reverse paddle key movement but the function messing the duration part.

	paddle* pad = pGame->getpaddle();
	pad->setspeed(-1 * pad->getspeed());
	int oldspeed = pad->getspeed();
	// apply duration or add timer
	pad->setspeed(oldspeed);
}

void collectable::QuickSand()
{
	// makes the paddle slower but the function messing the duration part.
	paddle* pad = pGame->getpaddle();
	int oldspeed = pad->getspeed();
	pad->setspeed(10);
	// apply duration or add timer
	pad->setspeed(oldspeed);
}

void collectable::WidePaddle()
{
	// gets paddle wider
	paddle* pad = pGame->getpaddle();
	int oldX = pad->getX();
	int oldW = pad->getWidth();
	int incValue = 15;
	pad->setWidth(oldW + incValue);
	pad->setX(oldX + incValue);
}

void collectable::NarrowPaddle()
{
	//gets paddle norrower
	paddle* pad = pGame->getpaddle();
	int oldX = pad->getX();
	int oldW = pad->getWidth();
	int decValue = 15;
	pad->setWidth(oldW - decValue);
	pad->setX(oldX - decValue);
}