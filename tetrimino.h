#pragma once
#include "colors.h"
#include<vector>

class orientation {

public:
	int row, col;
	orientation(int , int );
};

class tetrimino {

private:
	int singleCellSize, num, rowOffset, colOffset;
	colorClass clr;

public:
	int rotation;
	std::vector<orientation> cell[4];  //array of vectors
	tetrimino(int cs = 45, int r = 0, int ro = 0, int co = 0);
	void setNum(int n);
	int getNum();
	void draw(int, int);
	void move(int , int );
	std::vector<orientation> getPositions();
	virtual void rotate();
	void reverseRotation();
};

