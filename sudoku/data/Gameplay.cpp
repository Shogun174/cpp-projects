#include "Gameplay.hpp"
#include "colors.hpp"
#include <string>

void Gameplay::handleInput(Board& board, GameState& state, int& solvedCount)
{
	//player input:
	int key = GetKeyPressed();
	bool cellSelected = false;
	if (key == KEY_ESCAPE) 
	{
		//reset state and go back to menu:
		mistakes = 0;
		timer = 0.0f;
		state = MENU;
		if (solved) solvedCount++;
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Rectangle cell = {(float)(offsetX + cellSize * j), (float)(offsetY + cellSize * i), cellSize, cellSize};
			Vector2 mouse = GetMousePosition();
			if (CheckCollisionPointRec(mouse, cell))
			{
				//update selected cell's indices:
				selRow = i;
				selCol = j;
				cellSelected = true;
				//insert / erase a number in a cell:
				if (!solved)
				{
					if (board.grid[i][j] == 0 && key >= KEY_ONE && key <= KEY_NINE)
					{
						board.grid[i][j] = key - KEY_ZERO; //actual digit
						board.addedCells.insert({i, j});
						if (board.grid[i][j] != board.solvedGrid[i][j]) mistakes++;
					}
					else if (key == KEY_BACKSPACE && board.addedCells.count({i, j}))
					{
						board.grid[i][j] = 0;
						board.addedCells.erase({i, j});
					}
				}
			}
		}
	}
	if (!cellSelected)
	{
		selRow = -1;
		selCol = -1;
	}
}

void Gameplay::update(float dt, Board& board, Sound& music)
{
	solved = (board.grid == board.solvedGrid);
	if (!solved) timer += dt;
}

void Gameplay::draw(Board& board)
{
	BeginDrawing();
		ClearBackground(bgClearColor);
		DrawRectangle(offsetX + 20, offsetY + 20, boardSize, boardSize, shadowColor);
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
		//cell highlight:
		if (selRow != -1 && selCol != -1)
		{
			Rectangle cell = {(float)(offsetX + cellSize * selCol), (float)(offsetY + cellSize * selRow), cellSize, cellSize};
			DrawRectangleRec(cell, highlightColor);
		}
		//numbers:
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (board.grid[i][j] != 0)
				{
					//incorrect cell highlight:
					if (board.grid[i][j] != board.solvedGrid[i][j])
					{
						Rectangle cell = {(float)(offsetX + cellSize * j), (float)(offsetY + cellSize * i), cellSize, cellSize};;
						DrawRectangleRec(cell, incHighlightColor);
					}
					std::string numStr = std::to_string(board.grid[i][j]);
					int textWidth = MeasureText(numStr.c_str(), cellSize);
					int x = offsetX + (cellSize - textWidth) / 2 + cellSize * j;
					int y = offsetY + cellSize / 16 + cellSize * i;
					DrawText(numStr.c_str(), x, y, cellSize, BLACK);
				}
			}
		}
		//current game stats:
		std::string timerText = "Time: " + std::to_string(int(timer));
		std::string mistakeText = "Mistakes: " + std::to_string(mistakes);
		std::string statusText = std::string("Solved? ") + (solved ? "Yes!" : "No...");
		DrawText(timerText.c_str(), 5, 0, 32, BLACK);
		DrawText(mistakeText.c_str(), 5, 32, 32, (mistakes < 10 ? BLACK : RED));
		DrawText(statusText.c_str(), 5, 64, 32, (solved ? GREEN : BLACK));
	EndDrawing();
}