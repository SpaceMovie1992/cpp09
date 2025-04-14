#include "PmergeMe.hpp"

template <typename Container>
void PmergeMe::sortContainer(Container &container)
{
	int remaining = -1;
	if (container.size() % 2 != 0)
	{
		remaining = container.back();
		container.pop_back();
	}

	std::vector<std::pair<int, int>> pairs;
	for (size_t i = 0; i < container.size(); i += 2)
	{
		int first = container[i];
		int second = container[i + 1];
		if (first > second)
			std::swap(first, second);
		pairs.push_back({first, second});
	}

	std::vector<int> firstHalf, secondHalf;
	for (const auto &pair : pairs)
	{
		firstHalf.push_back(pair.first);
		secondHalf.push_back(pair.second);
	}
	std::sort(firstHalf.begin(), firstHalf.end());
	std::sort(secondHalf.begin(), secondHalf.end());

	container.clear();

	std::merge(firstHalf.begin(), firstHalf.end(), secondHalf.begin(),
			   secondHalf.end(), std::back_inserter(container));

	if (remaining != -1)
	{
		auto it = std::lower_bound(container.begin(), container.end(), remaining);
		container.insert(it, remaining);
	}
}