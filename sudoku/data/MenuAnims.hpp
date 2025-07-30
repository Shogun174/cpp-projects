#pragma once

#include "Game.hpp"
#include <string>
#include <vector>

struct Digit //helper
{
	public:
		int alpha = 0;
		int speed = 0;
		int fontSize = 0;
		float x = 0.0f;
		float y = 0.0f;
		bool increaseAlpha = false;
		std::string val;
		Digit(int n)
		{
			speed = GetRandomValue(200, 300);
			fontSize = GetRandomValue(100, 140);
			x = (float) GetRandomValue(0, Game::screenWidth - fontSize);
			y = (float) GetRandomValue(0, Game::screenHeight - fontSize);
			val = std::to_string(n);
		}
};

class MenuAnims
{
	public:
		float spawnTimerMax = 0.4f;
		float spawnTimer = spawnTimerMax;
		std::vector<Digit> digits;
		void boundsCheck(std::vector<Digit>& digits, size_t& i);
		void update(float dt, int anim);
		void draw();
};