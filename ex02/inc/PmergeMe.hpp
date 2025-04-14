#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

class PmergeMe
{
private:
	std::vector<int> vectorContainer;
	std::deque<int> dequeContainer;

	template <typename Container>
	void sortContainer(Container &container);

public:
	PmergeMe() = default;
	PmergeMe(const PmergeMe &other) = default;
	PmergeMe &operator=(const PmergeMe &other) = default;
	~PmergeMe() = default;

	bool parseArguments(int argc, char **argv);
	void sortData();
};

#include "PmergeMe.tpp"