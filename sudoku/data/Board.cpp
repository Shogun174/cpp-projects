#include "Board.hpp"

bool Board::isValidPos(const std::vector<std::vector<int>>& board, int row, int col, int num)
{
	//check the row and column:
	for (int i = 0; i < 9; i++)
	{
		if (board[row][i] == num || board[i][col] == num) return false;
	}
	//check the sub-grid:
	int startRow = row - row % 3;
	int startCol = col - col % 3;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[startRow + i][startCol + j] == num) return false;
		}
	}
	return true;
}

bool Board::solveSudoku(std::vector<std::vector<int>>& board, int row, int col)
{
	if (row == 9) return true; //solved
	else if (col == 9) return solveSudoku(board, row + 1, 0);
	else if (board[row][col] != 0) return solveSudoku(board, row, col + 1);
	else
	{
		//create a random sequence to check:
		std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		for (int i = 8; i >= 0; i--)
		{
			int j = GetRandomValue(0, i);
			std::swap(nums[i], nums[j]);
		}
		//check the numbers for validity:
		for (int i = 0; i < 9; i++)
		{
			if (isValidPos(board, row, col, nums[i]))
			{
				board[row][col] = nums[i];
				if (solveSudoku(board, row, col + 1)) return true;
				else board[row][col] = 0;
			}
		}
		return false;
	}
}

void Board::emptyCells(std::vector<std::vector<int>>& board, int k)
{
	//randomize which cells to empty:
	std::vector<int> indices(81, 0);
	for (int i = 0; i < 81; i++) indices[i] = i;
	for (int i = 80; i >= 0; i--)
	{
		int j = GetRandomValue(0, i);
		std::swap(indices[i], indices[j]);
	}
	//1 <= k <= 81, empty random k cells: (ignores puzzle difficulty)
	for (int i = 0; i < k; i++)
	{
		int row = indices[i] / 9;
		int col = indices[i] % 9;
		board[row][col] = 0;
	}
}

void Board::createNewPuzzle()
{
	grid = std::vector(9, std::vector<int>(9, 0)); //reset the grid
	(void) solveSudoku(grid, 0, 0);
	solvedGrid = grid;
	emptyCells(grid, GetRandomValue(35, 40));
}