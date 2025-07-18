#include "Menu.hpp"
#include "colors.hpp"

enum MenuButton {START = 0, EXIT = 1};

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
						state = GAMEPLAY;
						board.createNewPuzzle();
						break;
					}
					case EXIT:
						state = QUIT;
						break;
				}
			}
		}
	}
	if (!buttonSelected) selButton = -1;
}

void Menu::update(float dt)
{
	//do animations later
}

void Menu::draw()
{
	BeginDrawing();
		ClearBackground(bgClearColor);
		DrawText(titleText.c_str(), buttonX / 2 - 35, 100, 204, RED);
		DrawText(titleText.c_str(), buttonX / 2 - 40, 100, 204, BLACK);
		//buttons:
		for (size_t i = 0; i < buttons.size(); i++)
		{
			DrawRectangle(buttons[i].x + 20, buttons[i].y + 20, buttons[i].width, buttons[i].height, shadowColor); //shadow
			DrawRectangleRec(buttons[i], RAYWHITE);
			if (selButton == i) DrawRectangleRec(buttons[i], highlightColor);
			DrawRectangleLinesEx(buttons[i], 3.0f, BLACK);
			//draw labels:
			if (i == START) DrawText(startText.c_str(), buttons[i].x + buttons[i].width / 6, buttons[i].y + 20, 90, BLACK);
			else if (i == EXIT) DrawText(exitText.c_str(), buttons[i].x + buttons[i].width / 4, buttons[i].y + 20, 90, BLACK);
			//menu stats:
			std::string solvedText = "You have solved " + std::to_string(solvedCount) + " puzzles!";
			DrawText(solvedText.c_str(), buttonX - 30, 2 * buttonH + 55, 32, (solvedCount > 0 ? GREEN : RED));
		}
	EndDrawing();
}