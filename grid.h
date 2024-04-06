	#pragma once

	#include "drawable.h"
	#include "Bricks.h"


	class game;

	class grid:public drawable
	{

		brick*** brickMatrix;		//2D array of brick pointers
		int rows, cols;
		
	public:
		grid(point r_uprleft, int r_width, int r_height, game* r_pGame);
		~grid();
		void draw() const;
		void hide_brick_Matrix(point p);
		void hide_bricks_of_bombbrick(point p); // hide upper, lower, right, and left bricks around bombbrick
		int addBrick(BrickType brkType, point clickedPoint);
		brick*** getbrickmatrix();
	};

