#include "Game.hpp"
#include "Menu.hpp"
#include "Gameplay.hpp"
#include "Board.hpp"
#include <ctime>

void Game::run()
{
	InitWindow(screenWidth, screenHeight, "Sudoku");
	InitAudioDevice();
	SetExitKey(KEY_NULL); //disable escape key
	SetTargetFPS(60);
	Menu menu;
	Gameplay gameplay;
	//window icon:
	Image icon = LoadImage("./images/icon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);
	//background music:
	Sound music = LoadSound("./audio/void.ogg");
	SetSoundVolume(music, 0.75f);
	//create a sudoku puzzle:
	SetRandomSeed((unsigned int) time(nullptr)); //same as time(0) lmao
	Board board;
	board.createNewPuzzle();
	//main loop:
	while (currentState != QUIT && !WindowShouldClose())
	{
		float dt = GetFrameTime();
		if (!IsSoundPlaying(music)) PlaySound(music); //loop
		if (currentState == MENU)
		{
			menu.handleInput(board, currentState);
			menu.update(dt);
			menu.draw();
		}
		else if (currentState == GAMEPLAY)
		{
			gameplay.handleInput(board, currentState, menu.solvedCount);
			gameplay.update(dt, board, music);
			gameplay.draw(board);
		}
	}
	UnloadSound(music);
	CloseAudioDevice();
	CloseWindow();
}