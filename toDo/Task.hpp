#pragma once

#include <string>

struct Task
{
	public:
		int dueDate;
		std::string name;
		std::string priority;
		Task(int dueDate, std::string name, std::string priority)
		{
			this->dueDate = dueDate;
			this->name = name;
			this->priority = priority;
		}
};