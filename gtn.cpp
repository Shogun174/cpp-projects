#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <limits>

using namespace std;

enum ColorThreshold //magic numbers :P
{
	VERY_CLOSE = 4,
	CLOSE = 8,
	MID = 12,
	FAR = 16,
	VERY_FAR = 20
};

//guess the number game:
struct Game
{
	public:
		int diff = 0; //default easy mode
		unordered_map<int, function<void()>> menuOptions;
		unordered_map<int, char> colors;
		
		//input bindings to functions / range colors:
		Game() 
		{
			colors[VERY_CLOSE] = 'A'; //light green
			colors[CLOSE] = '2'; //green
			colors[MID] = 'E'; //light yellow
			colors[FAR] = '6'; //yellow
			colors[VERY_FAR] = 'C'; //light red
			menuOptions[1] = [this]() {start();};
			menuOptions[2] = [this]() {changeDifficulty();};
			menuOptions[3] = [this]() {howToPlay();};
			menuOptions[4] = [this]() {cout << "Bye! :)"; exit(0);};
		}
		
		void menu()
		{
			while (true) //infinite loop to come back after any menu choice
			{
				int input;
				cout << "\nSelect an option:\n";
				cout << "1. Start Game\n";
				cout << "2. Change Difficulty\n";
				cout << "3. How to Play\n";
				cout << "4. Exit\n";
				validInput(input);
				if (menuOptions.count(input)) menuOptions[input]();
				else cout << "Invalid input.\n\n";
			}
		}
		
		//game logic:
		void start()
		{
			//difficulty scaling:
			int attempts = 20;
			int range = 30;
			attempts -= diff * 5;
			range *= (diff + 1);
			bool running = true;
			int number = rand() % (range + 1); //0 - range
			
			//main loop:
			while (running)
			{	
				cout << "\nGuess the number! (" << attempts << " att.)\n";
				int input;	
				validInput(input);
				//did we guess it?
				if (input == number)
				{
					cout << "\nGuessed it! (" << attempts << " att.)\n";
					system("color 7"); //back to white
					running = false;
				}
				else //wrong answer
				{
					int d = abs(number - input); //difference
					//colored text: (Windows only, kek)
					for (int i = 1; i < 6; i++)
					{
						int limit = i * 4;
						if (d <= limit) //change color every 4 numbers
						{
							system((string("color ") + colors[limit]).c_str());
							break;
						}
						else if (i == 5 && d > limit) system("color 4"); //red (last check)
					}
					attempts--;
					cout << "Nope! ";
					//too low / too high:
					if (input > number) cout << "Too high!\n";
					else cout << "Too low!\n";
				}
				//game over:
				if (attempts == 0)
				{
					system("color 7"); //back to white
					running = false;
					cout << "\nGame over! The correct number was: " << number << ".\n";
					cout << "Better luck next time! :P\n";
				}
			}
		}
		
		void changeDifficulty()
		{
			int input;
			cout << "\nCurrent difficulty: " << diff << " (0 - easy, 1 - medium, 2 - hard)\n";
			cout << "Enter the new difficulty:\n";
			validInput(input);
			if (input == 0 || input == 1 || input == 2) //few options
			{
				diff = input;
				cout << "Done!\n";
			}
		}
		
		void howToPlay() //info dump
		{
			cout << "\nHow to play:\n";
			cout << "To win, you have to correctly guess the randomly generated number.\n";
			cout << "How many attempts you have and the number range varies by difficulty.\n";
			cout << "The greener the text, the closer you are to guessing the number!\n";
			cout << "Have fun! :P\n";
		}
	private: //helper functions
		void validInput(int& input)
		{
			//prevent invalid inputs: (we need numbers only!)
			while (!(cin >> input))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
};

int main()
{
	srand(time(0)); //random seed
	Game game;
	game.menu();
	return 0;
}