#pragma once

#include "Game.hpp"
#include "Board.hpp"
#include <string>
#include <vector>

class Menu
{
	public:
		std::string titleText = "SUDOKU";
		std::string startText = "Start";
		std::string exitText = "Exit";
		static constexpr float buttonW = Game::screenWidth / 3;
		static constexpr float buttonH = Game::screenHeight / 6;
		static constexpr float buttonX = Game::screenWidth / 2 - buttonW / 2; //center
		int selButton = -1;
		int solvedCount = 0;
		std::vector<Rectangle> buttons =
		{
			{buttonX, Game::screenHeight / 2, buttonW, buttonH}, //start
			{buttonX, Game::screenHeight / 2 + buttonH + 50, buttonW, buttonH} //exit
		};
		void handleInput(Board& board, GameState& state);
		void update(float dt);
		void draw();
};