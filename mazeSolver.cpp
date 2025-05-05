#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

//maze solver: (the red dot has to go the the yellow one in order for the maze to be solved)
int main()
{
	const int screenWidth = 1080;
	const int screenHeight = 720;
	InitWindow(screenWidth, screenHeight, "Maze Solver");
	SetTargetFPS(60);
	SetRandomSeed(time(0));
	//test data: (0 - path, 1 - wall)
	Vector2 seeker = {1, 1}; //interpolated values
	Vector2 target = {38, 18};
	std::vector<std::vector<int>> maze = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1, 0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1, 1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,1},
    {1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0, 0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1},
    {1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,0, 1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1},
    {1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1, 1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0, 0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1},
    {1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1, 1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,1, 0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
    {1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,0,0, 0,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1},
    {1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0, 0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,1},
    {1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1, 1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,1},
    {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1, 0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
    {1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1, 1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0, 0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1},
    {1,0,0,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1, 1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,1, 1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
	//variables:
	const int cols = maze[0].size();
	const int rows = maze.size();
	const int border = 25; //tile length
	const int mazeWidth = cols * border;
	const int mazeHeight = rows * border;
	const int offsetX = (screenWidth - mazeWidth) / 2;
	const int offsetY = (screenHeight - mazeHeight) / 2;
	const float moveTimerMax = 0.075;
	float moveTimer = moveTimerMax; //seconds until the seeker moves
	float timeElapsed = 0; 
	std::vector<Vector2> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; //four directions
	std::vector<Vector2> path; //the correct path points
	//visited points: (2D matrix acting as a hash map to avoid using a set or a map)
	std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false)); 
	Vector2 seekerStart = seeker; //where the seeker begins its current step
	Vector2 nextPoint = seeker; //where the seeker is heading next
	//main loop:
	while (!WindowShouldClose())
	{
		//update:
		float dt = GetFrameTime();
		moveTimer -= dt;
		timeElapsed += dt;
		float t = timeElapsed / moveTimerMax;
		if (t > 1.0f) t = 1.0f;
		seeker = Vector2Lerp(seekerStart, nextPoint, t); //movement interpolation
		//set a path point for the seeker:
		if (!Vector2Equals(seeker, target) && moveTimer <= 0)
		{
			bool hasMoved = false; //for checking if backtracking is needed
			moveTimer = moveTimerMax;
			timeElapsed = 0; //reset movement interpolation timer
			//shuffle the directions for random traversal routes:
			for (int i = 0; i < 4; i++) //for all directions
			{
				int swapA = GetRandomValue(0, 3);
				int swapB = GetRandomValue(0, 3);
				std::swap(dirs[swapA], dirs[swapB]);
			}
			//try moving the seeker in four directions:
			for (std::size_t i = 0; i < dirs.size(); i++)
			{
				Vector2 sum = Vector2Add(nextPoint, dirs[i]);
				//check if the sum point in the maze and is in bounds:
				if (sum.x >= 0 && sum.x <= maze[0].size() - 1
				&& sum.y >= 0 && sum.y <= maze.size() - 1 && maze[sum.y][sum.x] == 0)
				{
					if (!visited[sum.y][sum.x])
					{
						path.push_back(sum);
						nextPoint = sum;
						seekerStart = seeker;
						visited[sum.y][sum.x] = true;
						hasMoved = true;
						break; //avoid cases where there are multiple valid directions
					}	
				}
			}
			//dead end, time to backtrack:
			if (!hasMoved && path.size() > 1)
			{
				path.pop_back();
				nextPoint = path[path.size() - 1]; //previous good point
				seekerStart = seeker;
			}
		}
		else if (Vector2Equals(seeker, target)) //found the target, set a new target
		{
			path.clear();
			moveTimer = moveTimerMax;
			visited = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false)); 
			//regenerate until there's valid coordinates:
			do {
				target.x = GetRandomValue(0, cols - 1);
				target.y = GetRandomValue(0, rows - 1);
			} while (maze[target.y][target.x] == 1 || Vector2Equals(seeker, target));
		}
		//draw:
		BeginDrawing();
			ClearBackground(RAYWHITE);
			//the maze:
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{  
					//determine the color:
					int tile = maze[i][j]; //0 or 1
					unsigned char value = 255 - tile * 255; //white or black
					Color color = {value, value, value, 255}; 
					//center the tile:
					DrawRectangle(offsetX + border * j, offsetY + border * i, border, border, color);
				}
			}
			//seeker / target:
			DrawRectangle(offsetX + border * target.x, offsetY + border * target.y, border, border, YELLOW);
			DrawRectangle(offsetX + border * seeker.x, offsetY + border * seeker.y, border, border, RED);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
