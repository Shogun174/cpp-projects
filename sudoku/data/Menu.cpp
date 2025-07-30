#include "Menu.hpp"
#include "colors.hpp"

void Menu::handleInput(Board& board, GameState& state)
{
	Vector2 mouse = GetMousePosition();
	bool buttonSelected = false;
	for (size_t i = 0; i < buttons.size(); i++)
	{
		if (CheckCollisionPointRec(mouse, buttons[i]))
		{
			selButton = i;
			buttonSelected = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				switch (selButton)
				{
					case START:
					{
						currAnim = GetRandomValue(0, 3);
						menuAnims.digits.clear();
						menuAnims.spawnTimer = 0;
						state = GAMEPLAY;
						board.createNewPuzzle();
						break;
					}
					case EXIT: state = QUIT; break;
				}
			}
		}
	}
	if (!buttonSelected) selButton = -1;
}

void Menu::update(float dt)
{
	menuAnims.update(dt, currAnim);
}

void Menu::draw()
{
	BeginDrawing();
		menuAnims.draw();
		ClearBackground(bgClearColor);
		DrawText("SUDOKU", buttonX / 2 - 35, 100, 204, RED);
		DrawText("SUDOKU", buttonX / 2 - 40, 100, 204, BLACK);
		//buttons:
		for (size_t i = 0; i < buttons.size(); i++)
		{
			DrawRectangle(buttons[i].x + 20, buttons[i].y + 20, buttons[i].width, buttons[i].height, shadowColor); //shadow
			DrawRectangleRec(buttons[i], RAYWHITE);
			if (selButton == i) DrawRectangleRec(buttons[i], highlightColor);
			DrawRectangleLinesEx(buttons[i], 3.0f, BLACK);
			//draw labels:
			if (i == START) DrawText("Start", buttons[i].x + buttons[i].width / 6, buttons[i].y + 20, 90, BLACK);
			else if (i == EXIT) DrawText("Exit", buttons[i].x + buttons[i].width / 4, buttons[i].y + 20, 90, BLACK);
			//menu stats:
			std::string solvedText = "Puzzles solved: " + std::to_string(solvedCount);
			DrawText(solvedText.c_str(), buttonX + 42, 2 * buttonH + 55, 32, (solvedCount > 0 ? GREEN : RED));
			DrawText(solvedText.c_str(), buttonX + 40, 2 * buttonH + 55, 32, BLACK);
		}
	EndDrawing();
}