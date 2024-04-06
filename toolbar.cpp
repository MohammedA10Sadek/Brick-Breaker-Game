#include "toolbar.h"
#include "game.h"
#include "grid.h"
#include "gameConfig.h"


////////////////////////////////////////////////////  class toolbarIcon   ////////////////////////////////////////////////////
toolbarIcon::toolbarIcon(point r_uprleft, int r_width, int r_height, game* r_pGame):
	drawable(r_uprleft, r_width, r_height,  r_pGame)
{}




////////////////////////////////////////////////////  class iconAddNormalBrick   //////////////////////////////////////////////
iconAddNormalBrick::iconAddNormalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame):
	toolbarIcon(r_uprleft, r_width, r_height,  r_pGame)
{}

void iconAddNormalBrick::onClick()
{
	
	pGame->printMessage("Click on empty cells to add Normal Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;                          
		clicked.y = y;
	    grid* pGrid = pGame->getGrid();
		pGrid->addBrick(BRK_NRM, clicked);
		pGrid->draw();
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");

}

////////////////////////////////////////////////////  class iconExit   //////////////////////////////////////////////
iconExit::iconExit(point r_uprleft, int r_width, int r_height, game* r_pGame):
	toolbarIcon(r_uprleft, r_width, r_height,  r_pGame)
{}

void iconExit::onClick()
{
	//TO DO: add code for cleanup and game exit here
}


////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
toolbar::toolbar(point r_uprleft, int wdth, int hght, game* pG):
	drawable(r_uprleft, wdth, hght, pG)
{	
	
	height = hght;
	pGame = pG;

	//First prepare List of images for each icon
	//To control the order of these images in the menu, reoder them in enum ICONS above	
	iconsImages[ICON_ADD_NORM] = "images\\ToolbarIcons\\NormalBrickIcon.jpg";
	iconsImages[ICON_POWER_UP_DOWN] = "images\\ToolbarIcons\\PowerUpDownbrickIcon.jpg";
	iconsImages[ICON_HARD] = "images\\ToolbarIcons\\HardBrickIcon.jpg";
	iconsImages[ICON_BOMB] = "images\\ToolbarIcons\\bombbrickIcon.jpg";
	iconsImages[ICON_ROCK] = "images\\ToolbarIcons\\rockbrickIcon.jpg";
	iconsImages[ICON_LIVE] = "images\\ToolbarIcons\\LiveIcon.jpg";
	iconsImages[ICON_SAVE] = "images\\ToolbarIcons\\SaveIcon.jpg";
	iconsImages[ICON_LOAD] = "images\\ToolbarIcons\\LoadIcon.jpg";
	iconsImages[ICON_DELETE_BRICK] = "images\\ToolbarIcons\\DeleteBrickIcon.jpg";

	iconsImages[ICON_PLAY] = "images\\ToolbarIcons\\PlayIcon.jpg";
	iconsImages[ICON_PAUSE] = "images\\ToolbarIcons\\PauseIcon.jpg";
	iconsImages[ICON_CONTINUE] = "images\\ToolbarIcons\\ContinueIcon.jpg";
	iconsImages[ICON_STOP] = "images\\ToolbarIcons\\StopIcon.jpg";

	iconsImages[ICON_EXIT] = "images\\ToolbarIcons\\ExitIcon.jpg";

	point p;
	p.x = 0;
	p.y = 0;

	iconsList = new toolbarIcon* [ICON_COUNT];

	//For each icon in the tool bar
	//	1- Create an object setting its upper left corner, width and height
	iconsList[ICON_ADD_NORM] = new iconAddNormalBrick(p, config.iconWidth, height, pGame);
	p.x+= config.iconWidth;
	iconsList[ICON_POWER_UP_DOWN] = new IconPowerUpDownbrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_HARD] = new IconHardbrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_BOMB] = new IconBombbrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_ROCK] = new IconRockbrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_LIVE] = new IconLivebrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_SAVE] = new IconSave(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_LOAD] = new IconLoad(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_DELETE_BRICK] = new iconDeleteBrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;

	iconsList[ICON_PLAY] = new iconPlay(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_PAUSE] = new iconPause(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_CONTINUE] = new iconContinue(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_STOP] = new iconStop(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;

	iconsList[ICON_EXIT] = new iconExit(p, config.iconWidth, height, pGame);

	//	2-Set its image (from the above images list)
	for (int i = 0; i < ICON_COUNT; i++)
	{
		iconsList[i]->setImageName(iconsImages[i]);

	}
}



toolbar::~toolbar()
{
	for (int i = 0; i < ICON_COUNT; i++)
		delete iconsList[i];
	delete iconsList;
}



void toolbar::draw() const
{
	for (int i = 0; i < ICON_COUNT; i++)
		iconsList[i]->draw();
	window* pWind = pGame->getWind();
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, height, pWind->GetWidth(), height);

}

//handles clicks on toolbar icons, returns true if exit is clicked
bool toolbar::handleClick(int x, int y)
{
	if (x > ICON_COUNT * config.iconWidth)	//click outside toolbar boundaries
		return false;
	
	
	//Check whick icon was clicked
	//==> This assumes that menu icons are lined up horizontally <==
	//Divide x coord of the point clicked by the icon width (int division)
	//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

	int clickedIconIndex = (x / config.iconWidth);
	iconsList[clickedIconIndex]->onClick();	//execute onClick action of clicled icon

	if (clickedIconIndex == ICON_EXIT) return true;	
	
	return false;


}
////////////////////////////////////////////////////  class IconPowerUpDownbrick   //////////////////////////////////////////////
IconPowerUpDownbrick::IconPowerUpDownbrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{
}
void IconPowerUpDownbrick::onClick()
{
	pGame->printMessage("Click on empty cells to add Power Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;
		clicked.y = y;
		grid* pGrid = pGame->getGrid();
		pGrid->addBrick(BRK_POWER, clicked);
		pGrid->draw();
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");
}
////////////////////////////////////////////////////  class IconHardbrick   //////////////////////////////////////////////

IconHardbrick::IconHardbrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{
}
void IconHardbrick::onClick()
{
	pGame->printMessage("Click on empty cells to add Hard Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;
		clicked.y = y;
		grid* pGrid = pGame->getGrid();
		pGrid->addBrick(BRK_HRD, clicked);
		pGrid->draw();
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");
}
////////////////////////////////////////////////////  class IconBombbrick   //////////////////////////////////////////////

IconBombbrick::IconBombbrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{
}
void IconBombbrick::onClick()
{
	pGame->printMessage("Click on empty cells to add Bomb Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;
		clicked.y = y;
		grid* pGrid = pGame->getGrid();
		pGrid->addBrick(BRK_BOM, clicked);
		pGrid->draw();
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");
}
////////////////////////////////////////////////////  class IconRockbrick   //////////////////////////////////////////////

IconRockbrick::IconRockbrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{
}
void IconRockbrick::onClick()
{
	pGame->printMessage("Click on empty cells to add Rock Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;
		clicked.y = y;
		grid* pGrid = pGame->getGrid();
		pGrid->addBrick(BRK_ROCK, clicked);
		pGrid->draw();
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");
}
////////////////////////////////////////////////////  class IconLivebrick   //////////////////////////////////////////////

IconLivebrick::IconLivebrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{
}

void IconLivebrick::onClick()
{
	pGame->printMessage("Click on empty cells to add Live Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;
		clicked.y = y;
		grid* pGrid = pGame->getGrid();
		pGrid->addBrick(BRK_LIVE, clicked);
		pGrid->draw();
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");
}

////////////////////////////////////////////////////  class IconSave   //////////////////////////////////////////////

IconSave::IconSave(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{
}

void IconSave::onClick()
{
	
	// to add save logic
}
////////////////////////////////////////////////////  class IconLoad   //////////////////////////////////////////////

IconLoad::IconLoad(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{
}

void IconLoad::onClick()
{
	// to add load icon click logic
}

////////////////////////////////////////////////////  class iconDeleteBrick   //////////////////////////////////////////////

iconDeleteBrick::iconDeleteBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{
}

void iconDeleteBrick::onClick()
{
	pGame->printMessage("Click on a brick to be deleted  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;
		clicked.y = y;
		pGame->getGrid()->hide_brick_Matrix(clicked);
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");
}
////////////////////////////////////////////////////  class iconPlay   //////////////////////////////////////////////

iconPlay::iconPlay(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{
}

void iconPlay::onClick()
{
	pGame->play();
}
////////////////////////////////////////////////////  class iconPause   //////////////////////////////////////////////

iconPause::iconPause(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{
}

void iconPause::onClick()
{
	//ball stops
	pGame->getball()->balpause();
	//paddle stops
	pGame->getpaddle()->paddlepause();
	// timer pause counting
}
////////////////////////////////////////////////////  class iconContinue   //////////////////////////////////////////////

iconContinue::iconContinue(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{
}

void iconContinue::onClick()
{
	// ball continue
	pGame->getball()->ballcontinue();
	// paddle continue moving
	pGame->getpaddle()->paddlecontinue();
	// timer continue counting
}
////////////////////////////////////////////////////  class iconStop   //////////////////////////////////////////////

iconStop::iconStop(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{
}

void iconStop::onClick()
{
	pGame->~game();
	game newgame;
	newgame.go();

}

