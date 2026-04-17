#include "tetris.h"

game::game() {
	grd = Grid();
	shapes = getAllShapes();
	currentBlock = getRandomTetrimion();
	nextBlock = getRandomTetrimion();
	gameOver = false;
	score = 0;
	lines = 0;
	level = 1;
	InitAudioDevice();  //turns on the audio system
	bgMusic = LoadMusicStream("resources/audios/Tetris.mp3");  //loadinf music
	PlayMusicStream(bgMusic);  //starts playing the loaded music
	rotateSound = LoadSound("resources/audios/rotateSound.mp3");  // Load 3 short sound files into memory to use instantly
	clearSound = LoadSound("resources/audios/clearSound.mp3");
	GameOverSound = LoadSound("resources/audios/gameOver.mp3");
	style = LoadFontEx("resources/fonts/scoreF.otf", 64, 0, 0);
}

	tetrimino* game::getRandomTetrimion() {
		if (shapes.empty()) {
			shapes = getAllShapes();  //list is only refilled when it's empty...it is the list of pointers of vectors to the dynamic shapes
		}
		int randomIndex = rand() % shapes.size();         //can return 0,1,2,3,4,5,6
		tetrimino* block = shapes[randomIndex];           
		shapes.erase(shapes.begin() + randomIndex);       //shapes.erase() deletes the element at position randomIndex in the list
		return block;
	}
	std::vector<tetrimino*> game::getAllShapes() {    //returns dynamically created shapes
		return { new IShape(), new JShape() ,new LShape() ,new OShape(),new SShape() , new TShape(),new ZShape() };
	}
	void game::draw() {  //draws the grid and the blocks
		grd.draw();
		currentBlock->draw(100,40);
		nextBlock->draw(565, 800);
	}
	 
	float lastMoveTime = 0.0f; // Time since last move action
	float lastRotateTime = 0.0f; // Time since last rotate action

	void game::inputs() { 
		float currentTime = GetTime(); 

		if (gameOver && IsKeyPressed(KEY_R)) {
			gameOver = false;
			restart();
		}

		if (IsKeyPressed(KEY_LEFT)) {
			moveToLeft();
		}

		if (IsKeyPressed(KEY_RIGHT)) {
			moveToRight();
		}

		if (IsKeyDown(KEY_DOWN) && currentTime - lastMoveTime >= 0.1f){ //time between repeated key presses (in seconds)) {
			moveToDown();
			lastMoveTime = currentTime; //update the last move time
		}

		if (IsKeyDown(KEY_UP) && currentTime - lastRotateTime >= 0.2f) {
			rotate();
			lastRotateTime = currentTime; // Update the last rotate time
		}
	} 
	void game::moveToLeft() {  
		if (!gameOver) {
			currentBlock->move(0, -1);
			if (isOutside() || !canOccupy()) {
				currentBlock->move(0, 1);
			}
		}
	}
	void game::moveToRight() {   
		if (!gameOver) {

			currentBlock->move(0, 1);
			if (isOutside() || !canOccupy()) {
				currentBlock->move(0, -1);
			}
		}
	}  
	void game::moveToDown() { 
		if (!gameOver) {
			currentBlock->move(1, 0);
			if (isOutside() || !canOccupy()) {  //landed...
				currentBlock->move(-1, 0);
				dontMove();    // storing the block ids in the grid
			}
		}
	}
	bool game::isOutside() {  //sends each cell of a block to grid class ifOutside to check 
		std::vector<orientation> blocks = currentBlock->getPositions();  
		for (orientation item : blocks) {
			if (grd.ifOutside(item.row, item.col)) {
				return true;
			}
		}
		return false;
	}
	void game::rotate() {
		if (!gameOver) {
			currentBlock->rotate();
			if (isOutside() || !canOccupy()) {
				currentBlock->reverseRotation();
			}
			else {
				PlaySound(rotateSound);
			}
		}
	}
	void game::dontMove() {   //block lands when limit is reached while moving down
		std::vector<orientation> blocks = currentBlock->getPositions();
		for (orientation item : blocks) {
			grd.gridArray[item.row][item.col] = currentBlock->getNum();   // storing the block ids in the grid
		}
		currentBlock = nextBlock;   //Moves the stored nextBlock into play
		if (!canOccupy()) {  //next block cant occupy after the last block is locked
			gameOver = true;
			PlaySound(GameOverSound);
			PauseMusicStream(bgMusic);  //Pause music when game ends
		
		}
		nextBlock = getRandomTetrimion();
		int filled = grd.clearAndShiftRows();
		if (filled > 0) {
			PlaySound(clearSound);
			setScore(filled);
			setLines(filled);
			setLevel();
		}
	}
	bool game::canOccupy() {
		std::vector<orientation> blocks = currentBlock->getPositions();
		for (orientation item : blocks) {
			if (grd.ifEmpty(item.row, item.col) == false) {
				return false;
			}
		}
		return true;
	}
	void game::restart() {
		grd.setGrid();
		shapes = getAllShapes();
		currentBlock = getRandomTetrimion();
		nextBlock = getRandomTetrimion();
		score = 0;
		lines = 0;
		level = 1;
		/*delete currentBlock;
		delete nextBlock;
		for (tetrimino* b : shapes) {
			delete b;
		}*/
		shapes.clear();
		ResumeMusicStream(bgMusic);  //resume instead of reloading

	}
	void game::setScore(int rowsCleared) {
		score += (rowsCleared * 100);
	}
	int game::getScore() {
		return score;
	}
	void game::setLines(int filled) {
		lines+= filled;
	}
	int game::getLines() {
		return lines;
	}
	void game::setLevel() {
		if (lines / 10 > level - 1) {  
			level++;
			if (level > 8) {
				level = 1;  //back to level 1 after level 8
			}
		}
	}
	int game::getLevel() {
		return level;
	}
	void game::mainPrint() {

		if (gameOver) {
			DrawRectangle(0, 0, 1040, 970, Fade(BLACK, 0.85f));
			Vector2 goSize = MeasureTextEx(style, "GAME OVER", 120, 5);
			DrawTextEx(style, "GAME OVER", { (1040 - goSize.x) / 2, 400 }, 120, 5, WHITE);
			Vector2 subSize = MeasureTextEx(style, "Press R to restart or Esc to exit", 40, 3);
			DrawTextEx(style, "Press R to restart or Esc to exit", { (1040 - subSize.x) / 2, 540 }, 40, 3, WHITE);
		}
		else {
			
			std::string levelStr = std::to_string(getLevel()); 
			Vector2 levelSize = MeasureTextEx(style, (levelStr.c_str()), 35, 2);  //passes as c style string...returns the pixel size (Vector2) of the given text.
			DrawTextEx(style, levelStr.c_str(), { 730 + (250 - levelSize.x) / 10,150 }, 65, 5, WHITE);  //somewhat centered in a region of 250 pixels width.

			
			std::string scoreStr = std::to_string(getScore());
			Vector2 scoreSize = MeasureTextEx(style, (scoreStr.c_str()), 35, 2);
			DrawTextEx(style, scoreStr.c_str(), { 730 + (250 - levelSize.x) / 10,350 }, 65, 5, WHITE);

			
			std::string lineStr = std::to_string(getLines());
			Vector2 lineSize = MeasureTextEx(style, (lineStr.c_str()), 35, 2);
			DrawTextEx(style, lineStr.c_str(), { 730 + (250 - levelSize.x) / 10,550 }, 65, 5, WHITE);
		}
	}
	game::~game() {
		delete currentBlock;
		delete nextBlock;
		for (tetrimino* b : shapes) {
			delete b;
		}
		UnloadSound(GameOverSound);
		UnloadSound(rotateSound);
		UnloadSound(clearSound);
		UnloadMusicStream(bgMusic);
		CloseAudioDevice();  //turns off the audio system
	}