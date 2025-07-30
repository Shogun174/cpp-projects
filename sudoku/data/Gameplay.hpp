#pragma once

#include "Game.hpp"
#include "Board.hpp"

class Gameplay
{
	public:
		static constexpr int cellSize = 64;
		static constexpr int boardSize = 9 * cellSize;
		static constexpr int offsetX = Game::screenWidth / 2 - boardSize / 2;
		static constexpr int offsetY = Game::screenHeight / 2 - boardSize / 2;
		int mistakes = 0;
		int selRow = -1;
		int selCol = -1;
		float timer = 0.0f; //time elapsed solving
		bool solved = false;
		void handleInput(Board& board, GameState& state, int& solvedCount);
		void update(float dt, Board& board, Sound& music);
		void draw(Board& board);
};