#pragma once

#include <iostream>
#include <string>
#include <vector>

//an utility library for testing input: (compares actual and expected values)
namespace testcases 
{
	//results for basic data types:
	template <typename T>
	void equals(bool correct, const T& actual, const T& expected)
	{
		//using ANSI color codes:
		if (correct) std::cout << "\033[0;32m" << "Test passed.\n" << "\033[0m";
		else
		{
			std::cout << "\033[0;31m" << "Test failed";
			std::cout << ", expected: " << "\033[0m" << expected << "\033[0;31m";
			std::cout << ", actual: " << "\033[0m" << actual << "\n";
		}
	}
	//results for vectors:
	template <typename T>
	void equals(bool correct, const std::vector<T>& actual, const std::vector<T>& expected)
	{
		if (correct) std::cout << "\033[0;32m" << "Test passed.\n" << "\033[0m";
		else
		{
			//print the expected and actual vectors:
			std::cout << "\033[0;31m" << "Test failed";
			std::cout << ", expected: " << "\033[0m" << "[";
			for (std::size_t i = 0; i < expected.size(); i++)
			{
				std::cout << expected[i];
				if (i != expected.size() - 1) std::cout << ", ";
			}
			std::cout << "]" << "\033[0;31m" << ", actual: " << "\033[0m" << "[";
			for (std::size_t i = 0; i < actual.size(); i++)
			{
				std::cout << actual[i];
				if (i != actual.size() - 1) std::cout << ", ";
			}
			std::cout << "]\n";
		}
	}
	//assert for basic data types:
	template <typename T>
	void assert(const T& input, const T& answer) {equals(input == answer, input, answer);}
	void assert(const std::string& input, const std::string& answer) {equals(input == answer, input, answer);}
	//assert for vectors:
	template <typename T>
	void assert(const std::vector<T>& input, const std::vector<T>& answer)
	{
		//check if the vectors are equal:
		bool isTheSame = input.size() == answer.size();
		for (std::size_t i = 0; i < input.size() && isTheSame; i++)
		{
			if (input[i] != answer[i])
			{
				isTheSame = false;
				break;
			}
		}
		equals(isTheSame, input, answer);
	}
}
