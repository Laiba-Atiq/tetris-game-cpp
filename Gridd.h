#pragma once
#include<iostream>
#include<vector>
#include<raylib.h>
#include"colors.h"
#include"tetrimino.h"


class Grid {

private:
	int rows;
	int cols;
	int singleCellSize;
	colorClass clr;
	bool ifFull(int);
	void clearRow(int);
	void moveRowDown(int, int);

public:

	int gridArray[20][10];
	int filled = 0;

	Grid(int r = 20, int c = 10, int cs = 45);
	void setGrid();
	void draw();
	bool ifOutside(int , int );
	bool ifEmpty(int , int );
	int clearAndShiftRows();
	int getCols();
	int getRow();
};