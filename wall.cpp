#include "wall.h"
#include "game.h"
#include "gameConfig.h"

wall::wall(point r_uprleft, int wallWidth, int wallHight, game* r_pGame) :
	collidable(r_uprleft, wallWidth, wallHight, r_pGame) {}

void wall::draw() const
{

}
void wall::collisionAction()
{

}
