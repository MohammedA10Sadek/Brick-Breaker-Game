#pragma once
#include "collidable.h"
class wall : public collidable
{

public:
	wall(point r_uprleft, int wallWidth, int wallHight, game* r_pGame);
	void draw()const;
	void collisionAction();
};


