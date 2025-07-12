#pragma once

#include "Task.hpp"
#include <vector>
#include <unordered_map>

class App
{
	public:
		void run();
		void createTask();
		void changeTask();
		void deleteTask();
		//helpers:
		int selectTask();
		void showTasks();
		void validateInput(int& input);
		void validateInput(std::string& input);
	private:
		bool running = true;
		std::vector<Task> tasks;
};