#include <iostream>
#include <raylib.h>
#include"tetris.h"
#include<raylib.h>
#include <cstdlib>   
#include <ctime>     
#include<string>
#include<cmath>

using namespace std;

double lastTime = 0;
bool timeOfBlockDrop(double duration) {   //this function will be called 60 times per second
	double currentTime = GetTime();
	if (currentTime - lastTime >= duration) {
		lastTime = currentTime;
		return true;
	}
	return false;
}

int main() {

	InitWindow(1040, 970, "MyTetriss");
	Texture2D background = LoadTexture("resources/images/bg10.png");  //Loads an image
	SetTargetFPS(60);     //sets the speed of the game for each computer
	srand(time(NULL));
	Font fontStyle = LoadFontEx("resources/fonts/scoreF.otf", 64, 0, 0);
	game tetris = game();

	double interval = 1;
	int lastLines = 0;

	while (!WindowShouldClose()) {  // Detect window close button or ESC key
		UpdateMusicStream(tetris.bgMusic);  //keeps the music playing smoothly
		tetris.inputs();

		if (timeOfBlockDrop(interval)) { 
			tetris.moveToDown();
		}
		int currentLines = tetris.getLines();
		if (currentLines / 10 > lastLines / 10) {
			interval -= (interval * 0.1);
			lastLines = currentLines;  // Prevent multiple increments
		}
		if (tetris.getLevel() == 1) {
			interval = 1;
		}

		BeginDrawing();   //creates a blank canvas for the gamei.e draw a new fram
		DrawTexture(background, 0, 0, WHITE);  //draw bg at (0, 0)
		tetris.draw();
		tetris.mainPrint();				  

		EndDrawing();     //ends the drawing on canvas and shows it on frame
	}
	UnloadTexture(background);
	CloseWindow();

}