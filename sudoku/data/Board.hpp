#pragma once

#include <vector>
#include <utility>
#include <set>
#include <raylib.h>

class Board //grid data only
{
	public:
		std::vector<std::vector<int>> grid = std::vector(9, std::vector<int>(9, 0));
		std::set<std::pair<int, int>> addedCells; //rows and columns
		std::vector<std::vector<int>> solvedGrid;
		Board() {createNewPuzzle();}
		bool isValidPos(const std::vector<std::vector<int>>& board, int row, int col, int num);
		bool solveSudoku(std::vector<std::vector<int>>& board, int row, int col);
		void emptyCells(std::vector<std::vector<int>>& board, int k);
		void createNewPuzzle();
};