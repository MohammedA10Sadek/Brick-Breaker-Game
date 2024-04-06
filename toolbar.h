#pragma once

//This file contains all classes related to toolbar (toolbar icon classes & toolbar class itself)
#include "drawable.h"

////////////////////////////////////////////////////  class toolbarIcon   ////////////////////////////////////////////////////
//Base class for all toolbar icons 
class toolbarIcon :public drawable
{
public:
	toolbarIcon(point r_uprleft, int r_width, int r_height, game* r_pGame);
    virtual void onClick()=0;   //The action that should be taken when this icon is clicked
};

////////////////////////////////////////////////////  class iconAddNormalBrick   //////////////////////////////////////////////
class iconAddNormalBrick :public toolbarIcon
{
public:
	iconAddNormalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class IconPowerUpDownbrick   //////////////////////////////////////////////
class IconPowerUpDownbrick :public toolbarIcon
{
public:
	IconPowerUpDownbrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class IconHardbrick   //////////////////////////////////////////////
class IconHardbrick :public toolbarIcon
{
public:
	IconHardbrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class IconBombbrick   //////////////////////////////////////////////
class IconBombbrick :public toolbarIcon
{
public:
	IconBombbrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class IconRockbrick   //////////////////////////////////////////////
class IconRockbrick :public toolbarIcon
{
public:
	IconRockbrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class IconLivebrick   //////////////////////////////////////////////
class IconLivebrick :public toolbarIcon
{
public:
	IconLivebrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class IconSave   //////////////////////////////////////////////
class IconSave :public toolbarIcon
{
public:
	IconSave(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class IconLoad   //////////////////////////////////////////////
class IconLoad :public toolbarIcon
{
public:
	IconLoad(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class iconDeleteBrick   //////////////////////////////////////////////
class iconDeleteBrick :public toolbarIcon
{
public:
	iconDeleteBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class iconPlay   //////////////////////////////////////////////
class iconPlay :public toolbarIcon
{
public:
	iconPlay(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class iconPause    //////////////////////////////////////////////
class iconPause :public toolbarIcon
{
public:
	iconPause(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class iconContinue     //////////////////////////////////////////////
class iconContinue :public toolbarIcon
{
public:
	iconContinue(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class iconStop    //////////////////////////////////////////////
class iconStop :public toolbarIcon
{
public:
	iconStop(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};
////////////////////////////////////////////////////  class iconExit   //////////////////////////////////////////////
class iconExit :public toolbarIcon
{
public:
	iconExit(point r_uprleft, int r_width, int r_height, game* r_pGame);
	virtual void onClick();
};

////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
class toolbar:public drawable
{

	enum ICONS //The icons of the toolbar (you should add more icons)
	{
		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here
		ICON_ADD_NORM,		//add normal brick

		ICON_POWER_UP_DOWN, // powerup/down brick

		//TODO: Add more icons names here
		ICON_HARD,  
		ICON_BOMB,
		ICON_ROCK,
		ICON_LIVE,
		ICON_SAVE,
		ICON_LOAD,
		ICON_DELETE_BRICK,

		ICON_PLAY,
		ICON_PAUSE,
		ICON_CONTINUE,
		ICON_STOP,

		ICON_EXIT,		//Exit icon


		ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum

	};

private:
    toolbarIcon** iconsList; //an array of toolbarIcon pointers
	string iconsImages[ICON_COUNT];
	game* pGame;

public:
	toolbar(point r_uprleft, int r_width, int r_height, game* r_pGame);
	~toolbar();
    void draw() const;
	bool handleClick(int x, int y);	//handles clicks on toolbar icons, returns true if exit is clicked
};

