#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: ./MergeSorter <numbers>" << std::endl;
		return 1;
	}
	PmergeMe mergeSorter;
	if (!mergeSorter.parseArguments(argc, argv))
		return 1;
	mergeSorter.sortData();
	return 0;
}