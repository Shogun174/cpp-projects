#include "MenuAnims.hpp"
#include <utility>

void MenuAnims::boundsCheck(std::vector<Digit>& digits, size_t& i)
{
	Digit& digit = digits[i];
	if (digit.x + digit.fontSize < 0 || digit.x > Game::screenWidth ||
	digit.y + digit.fontSize < 0 || digit.y > Game::screenHeight)
	{
		std::swap(digit, digits.back());
		digits.pop_back();
		i--; //re-check swapped element
	}
}

void MenuAnims::update(float dt, int anim)
{
	spawnTimer -= dt;
	if (spawnTimer <= 0)
	{
		spawnTimer = spawnTimerMax;
		Digit newDigit(GetRandomValue(0, 9));
		digits.push_back(newDigit);
	}
	for (size_t i = 0; i < digits.size(); i++) 
	{
		Digit& d = digits[i];
		switch (anim)
		{
			case 0: d.y += d.speed * dt; break;
			case 1: d.y -= d.speed * dt; break;
			case 2: d.x += d.speed * dt; d.y += d.speed * dt; break;
			case 3: d.x -= d.speed * dt; d.y -= d.speed * dt; break;
		}
		d.alpha += (d.increaseAlpha ? 1 : -1);
		if (d.alpha <= 0) d.increaseAlpha = true;
		else if (d.alpha >= 255) d.increaseAlpha = false;
		boundsCheck(digits, i);
	}
}

void MenuAnims::draw()
{
	for (Digit& d : digits)
	{
		Color color = Fade(BLACK, d.alpha / 255.0f);
		DrawText(d.val.c_str(), d.x, d.y, d.fontSize, color);
	}
	std::string text = std::to_string(digits.size());
}