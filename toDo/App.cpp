#include "App.hpp"
#include <iostream>
#include <limits>
#include <algorithm>

void App::run()
{
	while (running)
	{
		int selected = 0; //default
		std::cout << "Select an option:\n";
		std::cout << "1. Create a task\n";
		std::cout << "2. Edit a task\n";
		std::cout << "3. Delete a task\n";
		std::cout << "4. Show tasks\n";
		std::cout << "5. Exit\n";
		do validateInput(selected); while (selected < 1 || selected > 5);
		switch (selected)
		{
			case 1:
				createTask();
				break;
			case 2:
				changeTask();
				break;
			case 3:
				deleteTask();
				break;
			case 4:
				showTasks();
				break;
			case 5:
				running = false;
				std::cout << "\nBye! :)";
		}
	}
}

void App::createTask()
{
	int dueDate = 0; //default
	std::string name;
	std::string priority;
	std::cout << "\nEnter the parameters for the new task:\n";
	std::cout << "Name (string): ";
	validateInput(name);
	std::cout << "Due date (int): ";
	validateInput(dueDate);
	std::cout << "Priority (string): ";
	validateInput(priority);
	Task newTask(dueDate, name, priority);
	tasks.push_back(newTask);
	std::cout << "\nTask created! :)\n\n";
}

void App::changeTask()
{
	if (tasks.size() > 0)
	{
		int selProperty = 0;
		int selTask = selectTask();
		std::cout << "\nEdit what?\n";
		std::cout << "1. Name\n";
		std::cout << "2. Due date\n";
		std::cout << "3. Priority\n\n";
		do validateInput(selProperty); while (selProperty < 1 || selProperty > 3);
		std::cout << "\nEnter a new value:\n";
		switch (selProperty)
		{
			case 1:
			{	
				std::string newName;
				validateInput(newName);
				tasks[selTask].name = newName;
				break;
			}
			case 2:
			{
				int newDate = 0;
				validateInput(newDate);
				tasks[selTask].dueDate = newDate;
				break;
			}
			case 3:
			{
				std::string newPriority;
				validateInput(newPriority);
				tasks[selTask].priority = newPriority;
				break;
			}
		}
		std::cout << "\nTask edited successfully! :)\n\n";
	}
	else std::cout << "\nThere are no tasks!\n\n";
}

void App::deleteTask()
{
	if (tasks.size() > 0)
	{	
		int selected = selectTask();
		tasks.erase(tasks.begin() + selected);
		std::cout << "Erased! :)\n\n";
	}
	else std::cout << "\nThere are no tasks!\n\n";
}

int App::selectTask()
{
	int index = 0; //default
	if (tasks.size() == 0) std::cout << "There are no tasks.\n";
	else
	{
		std::cout << "\nSelect task #: ";
		showTasks();
		do validateInput(index); while (index - 1 < 0 || index - 1 >= tasks.size());
	}
	return index - 1;
}
 
void App::showTasks()
{
	if (tasks.size() > 0)
	{
		std::cout << "\nTasks:\n";
		for (size_t i = 0; i < tasks.size(); i++)
		{
			std::cout << "#" << i + 1 << ": " << "\n";
			std::cout << "Name: " << tasks[i].name << "\n";
			std::cout << "Due date: " << tasks[i].dueDate << "\n";
			std::cout << "Priority: " << tasks[i].priority << "\n\n";
		}
	}
	else std::cout << "\nThere are no tasks!\n\n";
}

void App::validateInput(int& input)
{
	while (!(std::cin >> input))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	//ignore leftover string if user typed something like "123abc":
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void App::validateInput(std::string& input)
{
	while (!std::getline(std::cin, input) || input.empty()) {}
}