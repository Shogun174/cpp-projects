#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <ctime>
#include <algorithm>
#include <raylib.h>

bool isValidPos(const std::vector<std::vector<int>>& board, int row, int col, int num)
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

bool solveSudoku(std::vector<std::vector<int>>& board, int row, int col)
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

void emptyCells(std::vector<std::vector<int>>& board, int k)
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

int main()
{
	const int screenWidth = 1080;
	const int screenHeight = 720;
	const int cellSize = 64;
	const int boardSize = 9 * cellSize;
	const int offsetX = screenWidth / 2 - boardSize / 2; //grid offset x
	const int offsetY = screenHeight / 2 - boardSize / 2; //grid offset y
	int mistakes = 0;
	bool isSolved = false; //sudoku board status
	float timer = 0; //time elapsed solving
	InitWindow(screenWidth, screenHeight, "Sudoku");
	InitAudioDevice();
	SetTargetFPS(60);
	//background music:
	Sound music = LoadSound("./music.ogg");
	SetSoundVolume(music, 0.75f);
	PlaySound(music);
	//create a sudoku puzzle:
	SetRandomSeed((unsigned int) time(nullptr)); //same as time(0) lmao
	std::set<std::pair<int, int>> addedCells; //rows and columns of changed cells
	std::vector<std::vector<int>> grid(9, std::vector<int>(9, 0));
	(void) solveSudoku(grid, 0, 0);
	std::vector<std::vector<int>> solvedGrid = grid;
	emptyCells(grid, GetRandomValue(35, 40));
	//main loop:
	while (!WindowShouldClose())
	{
		//update:
		float dt = GetFrameTime();
		isSolved = (grid == solvedGrid);
		if (!isSolved) timer += dt;
		if (!IsSoundPlaying(music)) PlaySound(music); //loop
		//draw:
		BeginDrawing();
			ClearBackground({235, 235, 235, 255});
			DrawRectangle(offsetX + 20, offsetY + 20, boardSize, boardSize, {0, 0, 0, 160}); //shadow
			DrawRectangle(offsetX, offsetY, boardSize, boardSize, RAYWHITE);
			//normal borders:
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					int x = j * cellSize + offsetX;
					int y = i * cellSize + offsetY;
					DrawRectangleLines(x, y, cellSize, cellSize, BLACK);
				}
			}
			//thick borders:
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					float border = 3.0f * cellSize;
					float x = j * border + offsetX;
					float y = i * border + offsetY;
					DrawRectangleLinesEx({x, y, border, border}, 2.0f, BLACK);
				}
			}
			//numbers:
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (grid[i][j] != 0)
					{
						std::string numStr = std::to_string(grid[i][j]);
						int textWidth = MeasureText(numStr.c_str(), cellSize);
						int x = offsetX + (cellSize - textWidth) / 2 + cellSize * j;
						int y = offsetY + cellSize / 16 + cellSize * i;
						DrawText(numStr.c_str(), x, y, cellSize, BLACK);
					}
				}
			}
			//player input:
			int key = GetKeyPressed();
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					Rectangle cell = {(float)(offsetX + cellSize * j), (float)(offsetY + cellSize * i), cellSize, cellSize};
					Vector2 mouse = {(float)GetMouseX(), (float)GetMouseY()};
					if (CheckCollisionPointRec(mouse, cell))
					{
						//highlight a selectable cell:
						DrawRectangle(cell.x, cell.y, cell.width, cell.height, {215, 215, 215, 135});
						//insert / erase a number in a cell:
						if (grid[i][j] == 0 && key >= KEY_ONE && key <= KEY_NINE)
						{
							grid[i][j] = key - KEY_ZERO;
							addedCells.insert({i, j});
							if (grid[i][j] != solvedGrid[i][j]) mistakes++; //wrong!!!
						}
						else if (key == KEY_BACKSPACE && addedCells.count({i, j}))
						{
							grid[i][j] = 0;
							addedCells.erase({i, j});
						}
					}
					//incorrect number place highlight:
					if (grid[i][j] != 0 && grid[i][j] != solvedGrid[i][j])
					{
						DrawRectangle(cell.x, cell.y, cell.width, cell.height, {255, 0, 0, 135});
					}
				}
			}
			//current game stats:
			std::string timerText = "Time: " + std::to_string(int(timer));
			std::string mistakeText = "Mistakes: " + std::to_string(mistakes);
			std::string statusText = std::string("Solved? ") + (isSolved ? "Yes!" : "No...");
			DrawText(timerText.c_str(), 5, 0, 32, BLACK);
			DrawText(mistakeText.c_str(), 5, 32, 32, (mistakes < 10 ? BLACK : RED)); //trash if > 10 :P
			DrawText(statusText.c_str(), 5, 64, 32, (isSolved ? GREEN : BLACK));
		EndDrawing();
	}
	UnloadSound(music);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}