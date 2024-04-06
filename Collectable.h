#pragma once
#include "collidable.h"

class collectable : public collidable
{

public:
	collectable(point uprleft, int w, int h, game* r_pGame);
	void collisionAction() override;
	collectable* getCollectable();
	void doRandomAction();
	void WindGlid();
	void ReverseDirection();
	void QuickSand();
	void WidePaddle();
	void NarrowPaddle();
};