#pragma once

#include "Game.hpp"
#include "Board.hpp"
#include "MenuAnims.hpp"
#include <string>
#include <vector>

enum MenuButton {START = 0, EXIT = 1};

class Menu
{
	public:
		static constexpr float buttonW = Game::screenWidth / 3;
		static constexpr float buttonH = Game::screenHeight / 6;
		static constexpr float buttonX = Game::screenWidth / 2 - buttonW / 2; //center
		int currAnim = GetRandomValue(0, 3);
		int selButton = -1;
		int solvedCount = 0;
		std::vector<Rectangle> buttons =
		{
			{buttonX, Game::screenHeight / 2, buttonW, buttonH}, //start
			{buttonX, Game::screenHeight / 2 + buttonH + 50, buttonW, buttonH}, //exit
		};
		MenuAnims menuAnims;
		void handleInput(Board& board, GameState& state);
		void update(float dt);
		void draw();
};