#include <raylib.h>
#include <iostream>
#include <string>
#include <unordered_map>

class Barcode //class for easy barcode creation
{
	public:
		int barHeight = 128;
		int lineWidth = 2;
		std::string code; //1's and 0's (will draw this)
		std::string sideG = "101"; //left and right guards
		std::string midG = "01010"; //middle guard
		std::unordered_map<char, std::string> lCodes = //left side codes
		{
			{'0', "0001101"}, {'1', "0011001"}, {'2', "0010011"}, {'3', "0111101"},
			{'4', "0100011"}, {'5', "0110001"}, {'6', "0101111"}, {'7', "0111011"},
			{'8', "0110111"}, {'9', "0001011"}};
		std::unordered_map<char, std::string> rCodes = lCodes; //switched in the constructor
		std::string generateBarcode(std::string number) //input is a 12 digit number
		{
			//create the barcode string once:
			std::string barcode;
			barcode += sideG; //left guard
			//left side:
			for (size_t i = 0; i < number.size() / 2; i++)
			{
				barcode += lCodes[number[i]];
			}
			barcode += midG; //middle guard
			//right side:
			for (size_t i = number.size() / 2; i < number.size(); i++)
			{
				barcode += rCodes[number[i]];
			}
			barcode += sideG; //right guard
			return barcode;
		}
		//constructor:
		Barcode()
		{
			//flip the 0's and 1's for the right side codes:
			for (int i = 0; i < 10; i++)
			{
				char n = i + '0';
				for (char& c : rCodes[n]) c = ((c == '0') ? '1' : '0');
			}
		}
};

//UPC-A barcode visual:
int main()
{
	//initialization:
	const int windowWidth = 1080;
	const int windowHeight = 720;
	InitWindow(windowWidth, windowHeight, "UPC-A Barcode visualizer");
	SetTargetFPS(60);
	Barcode barcode; //a single object that will have its number rewritten by the user
	std::string input; //barcode number that the user will put in
	
	//screenshot variables:
	std::string filename = "barcode";
	std::string fileExtension = ".png";
	int picId = 0;

	//update:
	while (!WindowShouldClose())
	{	
		//screenshots:
		if (IsKeyPressed(KEY_ENTER)) 
		{
			TakeScreenshot((filename + std::to_string(picId) + fileExtension).c_str());
			picId++;
		}
		
		//barcode number input:
		int key = GetCharPressed();
		if (IsKeyPressed(KEY_BACKSPACE) && !input.empty()) input.pop_back();
		while (key >= '0' && key <= '9' && input.size() < 12) //digits only
		{
			input += char(key);
			key = GetCharPressed();
			//generate the barcode if there's enough digits:
			if (input.size() == 12) 
			{
				barcode.code = barcode.generateBarcode(input);
				std::cout << input << "\n";
				input = ""; //reset for new numbers
			}
		}
		
		//barcode size scaling:
		if (IsKeyPressed(KEY_DOWN))
		{
			//the barcode disappears if the width or height becomes 0:
			if (barcode.barHeight / 2 > 0 && barcode.lineWidth / 2 > 0)
			{
				barcode.barHeight /= 2;
				barcode.lineWidth /= 2;
			}
		}
		else if (IsKeyPressed(KEY_UP))
		{
			barcode.barHeight *= 2;
			barcode.lineWidth *= 2;
		}
		
		//draw:
		BeginDrawing();
			ClearBackground({215, 215, 215});
			//barcode:
			if (!barcode.code.empty())
			{
				int x = windowWidth / 2 - (barcode.code.size() * barcode.lineWidth) / 2;
				int y = windowHeight / 2 - barcode.barHeight / 2;
				//for each line:
				for (size_t i = 0; i < barcode.code.size(); i++)
				{
					Color lineColor = BLACK;
					if (barcode.code[i] == '0') lineColor = WHITE;
					DrawRectangle(x + i * barcode.lineWidth, y, barcode.lineWidth, barcode.barHeight, lineColor);
				}
			}
			//barcode number / input box:
			DrawText(("Number: " + input).c_str(), 0, 0, 30, RED);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}