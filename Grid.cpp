#pragma once
#include"Gridd.h"

Grid::Grid(int r, int c, int cs) : rows(r), cols(c), singleCellSize(cs) {
	setGrid();
}

	void Grid::setGrid() {    
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				gridArray[i][j] = 0;
			}
		}
	}

	void Grid::draw() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				int value = gridArray[i][j];
				DrawRectangle(j * singleCellSize + 100, i * singleCellSize + 40, singleCellSize - 1, singleCellSize - 1, clr[value]); //int posX, int posY, int width, int height, Color color
			}
		}
	}

	bool Grid::ifOutside(int r, int c) {   //is called in game class and checks for each tile of the block
		if (r >= 0 && r < rows && c >= 0 && c < cols) {   //here it checks a single tile
			return false;
		}
		return true;
	}

	bool Grid::ifEmpty(int r, int c) {
		if (gridArray[r][c] == 0) {
			return true;
		}
		return false;
	}

	bool Grid:: ifFull(int r) {  //checks if all the columns of a row are filled or not
		for (int i = 0; i < cols; i++) {
			if (gridArray[r][i] == 0) {
				return false;
			}
		}
		return true;
	}

	void Grid::clearRow(int r) {  //sets all the columns of a row equal to 0
		for (int i = 0; i < cols; i++) {
			gridArray[r][i] = 0;
		}
	}

	void Grid::moveRowDown(int r, int num) {  //num is the number of rows being shifted

		for (int i = 0; i < cols; i++) {
			gridArray[r + num][i] = gridArray[r][i];
			gridArray[r][i] = 0;
		}
	}

	int Grid::clearAndShiftRows() {   //combines ifFull, clearRow and clearAndShiftRows functions
		filled = 0;
		int completed = 0;
		for (int i = rows - 1; i >= 0; i--) { //starts checking from below
			if (ifFull(i)) {  //clears the number of rows that are full
				clearRow(i);

				filled++;
				completed++;
			}
			else if (completed > 0) {  //moves the number of rows cleared
				moveRowDown(i, completed);
			}
		}
		return filled;
	}

	//getters:
	int Grid::getCols() {
		return cols;
	}

	int Grid::getRow() {
		return rows;
	}
