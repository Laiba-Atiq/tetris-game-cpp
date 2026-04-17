#include"tetrimino.h"

orientation::orientation(int i , int j ) {  //assigns the values to the row and column positions 
		this->row = i;
		this->col = j;
	}

tetrimino::tetrimino(int cs, int r, int ro, int co) : singleCellSize(cs), rotation(r), rowOffset(ro), colOffset(co) {} 

void tetrimino::setNum(int n) {
	num = n;
}

int tetrimino::getNum() {
	return num;
}

std::vector<orientation> tetrimino::getPositions() {

	std::vector < orientation> block = cell[rotation];
	std::vector < orientation> movedBlocks;  //formedto store the new position of each tile considering the offset
	for (orientation item : block) {         //	for (int i = 0; i < block.size(); i++) { 
		orientation newOrientation = orientation(item.row + rowOffset, item.col + colOffset);
		movedBlocks.push_back(newOrientation);
	}
	return movedBlocks;
}

void tetrimino::draw(int x, int y) {
	std::vector<orientation> block = getPositions();       //block is the list of 4 small squares for the current rotation  //get sthe offset in getposition() function
	for (int i = 0; i < block.size(); i++) {               //draw a block tile by tile
		DrawRectangle(block[i].col * singleCellSize + x, block[i].row * singleCellSize + y, singleCellSize - 1, singleCellSize - 1, clr[num]);
	}
}

void tetrimino::move(int r, int c) { //called in child class to centeralize the block as soon as it is formed
	rowOffset += r;
	colOffset += c;
}

void tetrimino::rotate() {
	rotation++;
	if (rotation == 4) {
		rotation = 0;
	}
}

void tetrimino::reverseRotation() {
	rotation--;
	if (rotation == -1) {    //if it goes below 0 it wraps around to 3
		rotation = 4 - 1;  
	}
}

