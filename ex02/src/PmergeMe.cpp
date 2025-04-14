#include "PmergeMe.hpp"

bool PmergeMe::parseArguments(int argc, char **argv)
{
	if (argc < 2)
	{
		throw std::invalid_argument("Not enough numbers to sort");
	}

	for (int i = 1; i < argc; i++)
	{
		try
		{
			std::string input = argv[i];
			for (char c : input)
			{
				if (!std::isdigit(c))
				{
					throw std::invalid_argument("Invalid Input");
				}
			}
			int number = std::stoi(input);
			vectorContainer.push_back(number);
			dequeContainer.push_back(number);
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: " << e.what() << '\n';
			return false;
		}
	}
	return true;
}

void PmergeMe::sortData()
{
	std::cout << "Before: ";
	for (int num : vectorContainer)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;

	auto startVector = std::chrono::high_resolution_clock::now();
	sortContainer(vectorContainer);
	auto endVector = std::chrono::high_resolution_clock::now();

	auto startDeque = std::chrono::high_resolution_clock::now();
	sortContainer(dequeContainer);
	auto endDeque = std::chrono::high_resolution_clock::now();

	std::cout << "After: ";
	for (int num : vectorContainer)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;

	double vectorTime = std::chrono::duration<double, std::micro>(endVector - startVector).count();
	double dequeTime = std::chrono::duration<double, std::micro>(endDeque - startDeque).count();

	std::cout << "Time to process a range of " << vectorContainer.size()
			  << " elements with std::vector : " << vectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << dequeContainer.size()
			  << " elements with std::deque : " << dequeTime << " us" << std::endl;
}