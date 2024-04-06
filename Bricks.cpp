#include "Bricks.h"
#include "game.h"




////////////////////////////////////////////////////  class brick  ///////////////////////////////////////
brick::brick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	collidable(r_uprleft, r_width, r_height, r_pGame)
{
}

////////////////////////////////////////////////////  class normalBrick  /////////////////////////////////
normalBrick::normalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\bricks\\NormalBrick.jpg";


}

void normalBrick::collisionAction()
{
	

		pGame->setScore(1);

		//hide the normal brick() 
	    pGame->getGrid()->hide_brick_Matrix(uprLft);
		
	


}


////////////////////////////////////////////////////  class hardBrick  /////////////////////////////////
hardBrick::hardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	strength = 3;
	imageName = "images\\bricks\\hardbrick.jpg";

}

void hardBrick::collisionAction()
{

	
	//TODO: Add collision action logic
	


		strength--; // reduce strength by - 1 
		if (strength > 0) {
			// update score
			pGame->setScore(1);


		}
		else {
			// update score
			pGame->setScore(1);


			// hide brick 
			pGame->getGrid()->hide_brick_Matrix(uprLft);

		}
	
}

////////////////////////////////////////////////////  class bombBrick  /////////////////////////////////
bombBrick::bombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\bricks\\bombbrick.jpg";
}

void bombBrick::collisionAction()
{

	
	
		// hide bomb brick
	    pGame->getGrid()->hide_brick_Matrix(uprLft);
		// hide upper, lower, right, and left bricks
		pGame->getGrid()->hide_bricks_of_bombbrick(uprLft);
		//update score by +4
		pGame->setScore(4);
	
}
////////////////////////////////////////////////////  class rockBrick  /////////////////////////////////

rockBrick::rockBrick(point r_uprleft, int r_width, int r_height, game* r_pGame):
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\bricks\\rockbrick.jpg";

}

void rockBrick::collisionAction()
{
	
	//TODO: Add collision action logic
	// nothing will happen, just normal reflection
	
}
////////////////////////////////////////////////////  class LiveBrick  /////////////////////////////////
LiveBrick::LiveBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\bricks\\LiveBrick.jpg";

}

void LiveBrick::collisionAction()
{
	// updatescore
	pGame->setScore(1);
	// increase live
	pGame->SetLive(1); 
	// hide brick
	pGame->getGrid()->hide_brick_Matrix(uprLft);

}

////////////////////////////////////////////////////  class PowerUpDownbricks  /////////////////////////////////

PowerUpDownbricks::PowerUpDownbricks(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)

{
	imageName = "images\\bricks\\PowerUpDownbrick.jpg";

}

void PowerUpDownbricks::collisionAction()
{
	

	   // updatescore
	   pGame->setScore(1);
		// through down one collectable vertically 
	   
		// hide brick
		pGame->getGrid()->hide_brick_Matrix(uprLft);


	
}

