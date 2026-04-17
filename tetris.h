#pragma once  
#include"childTetriminos.h"
#include<vector>
#include<Random>
#include<string>
#include "Gridd.h"

class game {
	std::vector<tetrimino*> shapes;
	tetrimino* currentBlock;
	tetrimino* nextBlock;
	Sound rotateSound;
	Sound clearSound;
	Sound GameOverSound;
	bool isOutside();
	void rotate();
	void dontMove();
	bool canOccupy();



public:
	Music bgMusic;
	Grid grd;
	bool gameOver;
	int score;
	int lines;
	int level;
	Font style;

	game();
	~game();
	tetrimino* getRandomTetrimion();
	std::vector<tetrimino*> getAllShapes();
	void draw();
	void inputs();
	void moveToLeft();
	void moveToRight();
	void moveToDown();
	void restart();
	void setScore(int rowsCleared);
	int getScore();
	void setLines(int filled);
	int getLines();
	void setLevel();
	int getLevel();
	void mainPrint();
};