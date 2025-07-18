#pragma once

#include <raylib.h>

enum GameState {MENU, GAMEPLAY, QUIT};

class Game
{
	public:
		static constexpr int screenWidth = 1080;
		static constexpr int screenHeight = 720;
		GameState currentState = MENU;
		void run();
};