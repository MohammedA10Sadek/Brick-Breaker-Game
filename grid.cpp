#include "grid.h"
#include "game.h"
#include "gameConfig.h"

grid::grid(point r_uprleft, int wdth, int hght, game* pG):
	drawable(r_uprleft, wdth, hght, pG)
{

	rows = height / config.brickHeight;
	cols = width / config.brickWidth;

	brickMatrix = new brick ** [rows];
	for (int i = 0; i < rows; i++)
		brickMatrix[i] = new brick * [cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			brickMatrix[i][j] = nullptr;
}

grid::~grid()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (brickMatrix[i][j])
				delete brickMatrix[i][j];	//delete all allocated bricks

	for (int i = 0; i < rows; i++)
		delete brickMatrix[i];

	delete brickMatrix;

}

void grid::draw() const
{
	window* pWind = pGame->getWind();
	//draw lines showing the grid
	pWind->SetPen(config.gridLinesColor,1);

	//draw horizontal lines
	for (int i = 0; i < rows; i++) {
		int y = uprLft.y + (i + 1) * config.brickHeight;
		pWind->DrawLine(0, y, width, y);
	}
	//draw vertical lines
	for (int i = 0; i < cols; i++) {
		int x = (i + 1) * config.brickWidth;
		pWind->DrawLine(x, uprLft.y, x, uprLft.y+ rows* config.brickHeight);
	}

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (brickMatrix[i][j])
				brickMatrix[i][j]->draw();	//draw exisiting bricks


}

void grid::hide_brick_Matrix(point p)
{
	int r = (p.y - uprLft.y) / config.brickHeight;
	int c = p.x / config.brickWidth;
	point uprlft_b =  brickMatrix[r][c]->getuprlft();
	// get height and width of  a specific brick
	int width_b = brickMatrix[r][c]->getwidth();
	int height_b = brickMatrix[r][c]->getheight(); 

	delete brickMatrix[r][c];// I want to put i and j of the brick
	brickMatrix = nullptr;
	// add draw rectangle >> insert its points
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->SetPen(WHITE);
	pGame->getWind()->DrawRectangle(uprlft_b.x, uprlft_b.y, (uprlft_b.x + width_b), (uprlft_b.y + height_b), FILLED);
	
}
	


void grid::hide_bricks_of_bombbrick(point p)
{
	int r = (p.y - uprLft.y) / config.brickHeight;
	int c = p.x / config.brickWidth;
	// get all bricks uprlft points 
	// right brick
	point uprlft_R = brickMatrix[r + 1][c]->getuprlft();
	//left brick
	point uprlft_L = brickMatrix[r - 1][c]->getuprlft();
	// upper brick
	point uprlft_U = brickMatrix[r][c+1]->getuprlft();
	// down brick
	point uprlft_D = brickMatrix[r][c - 1]->getuprlft();

	
	// get height and width of all bricks
	// right
	int width_R = brickMatrix[r + 1][c]->getwidth();
	int height_R = brickMatrix[r + 1][c]->getheight();
	//left brick
	int width_L = brickMatrix[r - 1][c]->getwidth();
	int height_L = brickMatrix[r - 1][c]->getheight();
// upper brick
	int width_U = brickMatrix[r + 1][c + 1]->getwidth();
	int height_U = brickMatrix[r + 1][c + 1]->getheight();
// down brick
	int width_D = brickMatrix[r + 1][c - 1]->getwidth();
	int height_D = brickMatrix[r + 1][c - 1]->getheight();

	delete brickMatrix[r+1][c];// right brick
	delete brickMatrix[r-1][c];// left brick
	delete brickMatrix[r][c+1];// upper brick
	delete brickMatrix[r][c-1];// lower brick

	brickMatrix = nullptr;
	// add draw rectangle >> insert its points 
	// Right
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->SetPen(WHITE);
	pGame->getWind()->DrawRectangle(uprlft_R.x, uprlft_R.y, (uprlft_R.x + width_R), (uprlft_R.y + height_R), FILLED);
	// left
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->SetPen(WHITE);
	pGame->getWind()->DrawRectangle(uprlft_L.x, uprlft_L.y, (uprlft_L.x + width_L), (uprlft_L.y + height_L), FILLED);
	// upper
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->SetPen(WHITE);
	pGame->getWind()->DrawRectangle(uprlft_U.x, uprlft_U.y, (uprlft_U.x + width_U), (uprlft_U.y + height_U), FILLED);
	// down
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->SetPen(WHITE);
	pGame->getWind()->DrawRectangle(uprlft_D.x, uprlft_D.y, (uprlft_D.x + width_D), (uprlft_D.y + height_D), FILLED);

	
}



int grid::addBrick(BrickType brkType, point clickedPoint)
{
	//TODO:
	// 1- Check that the clickedPoint is within grid range (and return -1)
	// 2- Check that the clickedPoint doesnot overlap with an exisiting brick (return 0)

	//Here we assume that the above checks are passed
	
	//From the clicked point, find out the index (row,col) of the corrsponding cell in the grid
	int gridCellRowIndex = (clickedPoint.y-uprLft.y) / config.brickHeight;
	int gridCellColIndex = clickedPoint.x / config.brickWidth;

	//Now, align the upper left corner of the new brick with the corner of the clicked grid cell
	point newBrickUpleft;
	newBrickUpleft.x = uprLft.x + gridCellColIndex * config.brickWidth;
	newBrickUpleft.y = uprLft.y+ gridCellRowIndex * config.brickHeight;

	switch (brkType)
	{
	case BRK_NRM:	//The new brick to add is Normal Brick
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new normalBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	case BRK_POWER:	
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new PowerUpDownbricks(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	case BRK_HRD:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new hardBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	case BRK_BOM:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new bombBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	case BRK_ROCK:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new rockBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
	case BRK_LIVE:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new LiveBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;


		
	}
	return 1;
}

brick*** grid::getbrickmatrix()
{
	return brickMatrix;
}
