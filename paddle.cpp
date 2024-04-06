#include "paddle.h"
#include "game.h"
#include "CMUgraphicsLib\auxil.h"	// where Pause is found
paddle::paddle(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	collidable(r_uprleft, r_width, r_height, r_pGame) {
	speed = 15;
}



void paddle::draw()
{
	window* win = pGame->getWind();
		win->SetBrush(CORNFLOWERBLUE);
	win->SetPen(BLACK);
	win->DrawRectangle(pGame->getpaddle()->uprLft.x, pGame->getpaddle()->uprLft.y, (pGame->getpaddle()->uprLft.x + width), (pGame->getpaddle()->uprLft.y + height), FILLED);
}

void paddle::collisionAction()
{
}

void paddle::movement()
{// paddle movement function that responsible for both the draw and the movement of the paddle
	window* win = pGame->getWind();

	
		paddle::draw();
		char Key;
		keytype ktype;
		ktype = win->WaitKeyPress(Key);

		if (Key == 4 && uprLft.x != 0)
		{
			uprLft.x -= 15;
		}
		if (Key == 6 && uprLft.x < 1200 - width) {
			uprLft.x += 15;
		}
		win->SetBrush(LAVENDER);
		win->SetPen(LAVENDER);
		win->DrawRectangle(0, uprLft.y, (1200), (uprLft.y + height), FILLED);
		win->UpdateBuffer();
	
}
void paddle::setspeed(int newspeed)
{
	speed = newspeed;
}
int paddle::getspeed()
{
	return speed;
}
void paddle::setX(int x)
{
	uprLft.x = x;
}
int paddle::getX()
{
	return uprLft.x;
}
void paddle::setWidth(int w)
{
	width = w;
}

point paddle::getuprlft() const
{
	return uprLft;
}

int paddle::getWidth() const
{
	return width;
}

void paddle::paddlepause()
{
	isPause = true;
}

bool paddle::getisPause()
{
	return isPause;
}

const void paddle::paddlecontinue()
{
	isPause = false;
}
