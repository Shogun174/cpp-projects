#include <raylib.h>
#include <deque>
#include <string>

//mouse trail:
int main()
{
	InitWindow(1080, 720, "Mouse Trail");
	SetTargetFPS(60);
	const int maxPoints = 30; //maximum amount of trail points for the mouse
	std::deque<Vector2> coords; //mouse dot coordinates that make up the trail
	//main loop:
	while (!WindowShouldClose())
	{	
		//update:
		Vector2 mousePoint = GetMousePosition();
		coords.push_back(mousePoint);
		if (coords.size() > maxPoints) coords.pop_front();
		//draw:
		BeginDrawing();
			ClearBackground(RAYWHITE);
			if (coords.size() > 1) //need at least two points to run
			{
				//connect the points with lines:
				for (size_t i = 0; i < coords.size() - 1; i++) 
				{
					unsigned char alpha = float(i) * 255 / (coords.size() - 1);
					Color pointColor = {0, 0, 0, alpha}; //for the fade effect
					DrawLine(coords[i].x, coords[i].y, coords[i + 1].x, coords[i + 1].y, pointColor); 
				}
			}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
