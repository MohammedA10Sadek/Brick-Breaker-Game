#pragma once
#include "collidable.h"



// This class should contain all paddle-related featues like movement, shape, and collisions
class paddle : public collidable
{
private:
	bool isPause = false;
	int speed;

public:
	paddle(point uprleft, int w, int h, game* r_pGame);


	void draw();
	void collisionAction() override;
	void movement();
	void setspeed(int newspeed);
	int getspeed();
	void setX(int x);
	int getX();
	void setWidth(int w);
	point getuprlft() const;
	int getWidth() const;
	void paddlepause();
	bool getisPause(); const
	void paddlecontinue();


}; 
