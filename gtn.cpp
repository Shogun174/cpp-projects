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
		//default difficulty:
		int defAttempts = 20;
		int defRange = 100;
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
				else cout << "Invalid input. Enter a positive number.\n\n";
			}
		}
		
		//game logic:
		void start()
		{
			int attempts = defAttempts;
			int range = defRange;
			bool running = true;
			int number = rand() % (range + 1); //0 - range (both included)
			//main loop:
			while (running)
			{	
				cout << "\nGuess the number! (" << attempts << " att. left)\n";
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
					//colored text: (windows only)
					int d = abs(number - input); //difference
					for (int i = 1; i < 6; i++)
					{
						//using enums for color range calculation:
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
					running = false;
					system("color 7"); //back to white
					cout << "\nGame over! The correct number was: " << number << ".\n";
					cout << "Better luck next time! :P\n";
				}
			}
		}
		
		void changeDifficulty()
		{
			cout << "\nHere, you can change the number of guessing attempts and the range of the numbers.\n";
			cout << "Current difficulty: " << defAttempts << " attempts, " << defRange << " is the highest possible number.\n";
			cout << "Enter the new attempt number and the new maximum range:\n";
			cout << "(numbers will be picked from the interval [0; new range])\n";
			defAttempts = getPositiveInput();
			defRange = getPositiveInput();
			cout << "Changed the number of attempts! (now " << defAttempts << ")\n";
			cout << "Changed the maximum range number! (now " << defRange << ")\n";
		}
		
		void howToPlay() //info dump
		{
			cout << "\nHow to play:\n";
			cout << "To win, you have to correctly guess the randomly generated number.\n";
			cout << "You can enter the number of attempts and the range of possible numbers in the 'Change Difficulty' section.\n";
			cout << "The greener the text, the closer you are to guessing the number!\n";
			cout << "Have fun! :P\n";
		}
	private: //helper functions
		void validInput(int& input)
		{
			//prevent invalid inputs: (we need positive numbers only!)
			while (!(cin >> input))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}	
		int getPositiveInput()
		{
			int input;
			do {
				validInput(input);
				if (input <= 0) cout << "Invalid input. Enter a positive number.\n";
			} while (input <= 0);
			return input;
		}
};

int main()
{
	srand(time(0)); //random seed
	Game game;
	game.menu();
	return 0;
}
