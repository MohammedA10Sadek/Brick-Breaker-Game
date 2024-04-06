#include "game.h"
#include "gameConfig.h"



game::game()
{
	//Initialize playgrond parameters
	gameMode = MODE_DSIGN;


	//1 - Create the main window
	pWind = CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);

	//2 - create and draw the toolbar
	point toolbarUpperleft;
	toolbarUpperleft.x = 0;
	toolbarUpperleft.y = 0;

	gameToolbar = new toolbar(toolbarUpperleft, 0, config.toolBarHeight, this);
	gameToolbar->draw();

	//3 - create and draw the grid
	point gridUpperleft;
	gridUpperleft.x = 0;
	gridUpperleft.y = config.toolBarHeight;
	bricksGrid = new grid(gridUpperleft, config.windWidth, config.gridHeight, this);
	bricksGrid->draw();

	//4- Create the Paddle
	//TODO: Add code to create and draw the paddle
	point paddleUprleft;
	paddleUprleft.x = 525;
	paddleUprleft.y = 510;
	ppaddle = new paddle(paddleUprleft, 160, 17, this);
	// for showing the paddle draw function should be after movement function.
	ppaddle->draw();


	//5- Create the ball
	//TODO: Add code to create and draw the ball
	point ballUprleft;
	ballUprleft.x = paddleUprleft.x + 160 / 2;
	ballUprleft.y = paddleUprleft.y - 17 / 2;
	pball = new ball(ballUprleft, 160, 17, this);
	pball->balldraw();
	//6- Create and clear the status bar
	clearStatusBar();


}

game::~game()
{
	delete pWind;
	delete gameToolbar;
	delete bricksGrid;
	delete ppaddle;
	delete pball;
	delete pcollect;

}

void game::setScore(int s)
{

	score += s;


}

void game::SetLive(int L)
{
	live = live + L;
}







void game::DrawScore_live_timer()
{
	clearStatusBar();	//First clear the status bar
	// write score
	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), "Score: ");
	pWind->DrawInteger(80, config.windHeight - (int)(0.85 * config.statusBarHeight), score);
	//write live
	pWind->DrawString(101, config.windHeight - (int)(0.85 * config.statusBarHeight), "| Live: ");
	pWind->DrawInteger(165, config.windHeight - (int)(0.85 * config.statusBarHeight), live);
	//write time counter
	pWind->DrawString(186, config.windHeight - (int)(0.85 * config.statusBarHeight), "| Time: ");
	pWind->DrawInteger(260, config.windHeight - (int)(0.85 * config.statusBarHeight), seconds);
}


clicktype game::getMouseClick(int& x, int& y) const
{
	return pWind->WaitMouseClick(x, y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
window* game::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(config.bkGrndColor);
	pW->SetPen(config.bkGrndColor, 1);
	pW->DrawRectangle(0, 0, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void game::clearStatusBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void game::printMessage(string msg) const	//Prints a message on status bar
{
	clearStatusBar();	//First clear the status bar

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);
}



window* game::getWind() const		//returns a pointer to the graphics window
{
	return pWind;
}

paddle* game::getpaddle() const
{
	return ppaddle;
}




string game::getSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}

grid* game::getGrid() const
{
	// TODO: Add your implementation code here.
	return bricksGrid;
}

ball* game::getball() const
{
	return pball;
}

collectable* game::getCollectable() const
{
	return pcollect;
}

void game::checkBallFall()
{
	if (pball->getYPosition() >= pWind->GetHeight() - (pball->getYPosition() + 10))
	{
		live--;
		pball->setresetposition();
		if (live == 0)
		{
			pWind->DrawRectangle(0, 0, pWind->GetWidth(), pWind->GetHeight(), FILLED);
			printMessage("game over");
		}
	}
}



////////////////////////////////////////////////////////////////////////
void game::go() const
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	bool isExit = false;
	char c;
	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - Brick Breaker (CIE202-project) - - - - - - - - - -");

	do
	{



		//Get the coordinates of the user click
		if (gameMode == MODE_DSIGN)		//Game is in the Desgin mode
		{
			printMessage("Ready...");
			getMouseClick(x, y);
			//[1] If user clicks on the Toolbar
			if (y >= 0 && y < config.toolBarHeight)
			{
				isExit = gameToolbar->handleClick(x, y);


			}

		}
		if (gameMode == MODE_PLAY) {
			if (ppaddle->getisPause() == false) {
				ppaddle->movement();
			}
			if (pball->getisPause() == false) {
				pball->ballMovement();
			}
		}
		//	char key;
		//	keytype ktype;
		//	
		//	if (key == 32) {
		//		do {
		//			pWind->GetMouseClick(x, y);
		//			ktype = pWind->GetKeyPress(key);
		//			//[1] If user clicks on the Toolbar
		//			if (y >= 0 && y < config.toolBarHeight)
		//			{
		//				isExit = gameToolbar->handleClick(x, y);

		//			}
		//			// if ball collides with any brick
		//			brick*** brickMatrix = bricksGrid->getbrickmatrix();
		//			int rows = bricksGrid->getheight() / config.brickHeight;
		//			int cols = bricksGrid->getwidth() / config.brickWidth;
		//			for (int i = 0; i < rows; i++) {
		//				for (int j = 0; i < cols; j++) {
		//					//DrawScore_live_timer();
		//					// paddle and ball movement 
		//					if (ppaddle->getisPause() == false) {
		//						ppaddle->movement();
		//					}
		//					if (pball->getisPause() == false) {
		//						pball->ballMovement();
		//					}
		//					// if check collision between ball and paddle true, do feature 20, 
		//					collisionInfo BallPaddleCollision = checkCollision(ppaddle, pball);
		//					if (BallPaddleCollision.collided) {
		//						pball->setcollisionpoint(BallPaddleCollision.midpoint);
		//						pball->BallPaddleReflection();
		//					}
		//					//////////////////////////////////
		//					//next part related to collison of bricks
		//					collisionInfo BallBrickCollision = checkCollision(brickMatrix[i][j], pball);
		//					if (BallBrickCollision.collided) {
		//						pball->setcollisionpoint(BallBrickCollision.midpoint);
		//						pball->BallBrickReflection(i, j);
		//					}
		//					/////////////////////////////////
		//					// check collision between paddle and collectable
		//					collisionInfo PaddleCollectableCollision = checkCollision(ppaddle, pcollect);
		//					if (PaddleCollectableCollision.collided) {
		//						pcollect->doRandomAction();
		//					}
		//				}
		//			}
		//		} while (live != 0);
		//	}

		//}
		} while (!isExit);

	}


//////////////////////////////////////////////////////////////////////////////////////////////////
// if play icon clicked, call play
void game::play()
{

	gameMode = MODE_PLAY;


	pWind->ChangeTitle("- - - - - - - - - - Brick Breaker (CIE202-project) - - - - - - - - - -");
	printMessage("Enter Space to start");



	//// hide bricks icon and their action 
	//gameToolbar->~toolbar();
	//delete gameToolbar;
	//gameToolbar = nullptr;
	//
	////2 - create and draw the toolbar
	//point toolbarUpperleft;
	//toolbarUpperleft.x = 0;
	//toolbarUpperleft.y = 0;

	//gameToolbar = new toolbar(toolbarUpperleft, 0, config.toolBarHeight, this, true);
	//gameToolbar->draw();
	 //when space is clicked, move ball
	go();
	//char key;
	//keytype ktype;
	//ktype = pWind->WaitKeyPress(key);
	//if (key == 32)
	//{
	//	// move ball
	//	pball->ballMovementVertically();


	//}
}
