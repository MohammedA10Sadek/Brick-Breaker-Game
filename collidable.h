#pragma once
#include "drawable.h"

//================================================================================================
 ///////////////////////////////////////////////////////////////////////////////////////////////
 //define a struct containing collision information
struct collisionInfo {
    bool collided; // checks if a collision occurred
    point midpoint; // point of collition
};


class collidable :public drawable
{
public:
    collidable(point r_uprleft, int r_width, int r_height, game* r_pGame);
    friend collisionInfo checkCollision(const collidable* obj1, const collidable* obj2);
    virtual void collisionAction() = 0;    //action that should be performed upon collision
    ///////////////////////////////////////   collidable classes   /////////////////////////////////
//Base class for all collidable (objects that may collide with other objects)
    struct collisionInfo {
        bool collisionstate = true; // checks if a collision occurred
        point midpoint;// point of collition
    };
};