#pragma once


//This file contains all classes bricks classes 
#include "collidable.h"

enum BrickType	//add more brick types
{
	BRK_NRM,	//Normal Brick
	BRK_HRD,		//Hard Brick
	BRK_BOM,         // Bomb brick
	BRK_ROCK,        // Rock brick
	BRK_LIVE,            //live brick
	BRK_POWER           // powerup/down brick

	//TODO: Add more types
};

////////////////////////////////////////////////////  class brick  ///////////////////////////////////////
//Base class for all bricks
class brick :public collidable
{
public:
	brick(point r_uprleft, int r_width, int r_height, game* r_pGame);


};


////////////////////////////////////////////////////  class normalBrick  /////////////////////////////////
class normalBrick :public brick
{
public:
	normalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};


////////////////////////////////////////////////////  class hardBrick  /////////////////////////////////
class hardBrick :public brick
{
private:
	int strength;

public:
	hardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};

////////////////////////////////////////////////////  class bombBrick  /////////////////////////////////
class bombBrick :public brick
{
public:
	bombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};
////////////////////////////////////////////////////  class RockBrick  /////////////////////////////////
class rockBrick :public brick
{
public:
	rockBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};
////////////////////////////////////////////////////  class LiveBrick  /////////////////////////////////
class LiveBrick :public brick
{
public:
	LiveBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};
////////////////////////////////////////////////////  class PowerUpDownbricks  /////////////////////////////////
class PowerUpDownbricks :public brick
{
public:
	PowerUpDownbricks(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};


