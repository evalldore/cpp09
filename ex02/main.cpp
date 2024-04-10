#include <iostream>
#include <cstdlib>
#include "PmergeMe.hpp"

static bool init(std::vector<int>& vec, std::deque<int>& deq, int argc, char *argv[]) {
	int		value;
	char	*end;
	for (int index = 1; index < argc; index++) {
		value = static_cast<int>(strtol(argv[index], &end, 10));
		if (*end || value < 0)
			return false;
		vec.push_back(value);
		deq.push_back(value);
	}
	return true;
}

static void printVec(const std::vector<int>& vec) {
	std::vector<int>::const_iterator it;

	for (it = vec.begin(); it != vec.end(); it++) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		std::cerr << "Not enough arguments in parameters!" << std::endl;
		return 1;
	}
		
	std::vector<int> intVec;
	std::deque<int> intDeque;

	if (!init(intVec, intDeque, argc, argv)) {
		std::cerr << "Error: Invalid parameters" << std::endl;
		return 1;
	}
	std::cout << "Before: ";
	printVec(intVec);
	clock_t startVec = clock();
	fordJohnsonMergeInsertionSort(intVec, 0, intVec.size() - 1);
	clock_t endVec = clock();
	clock_t startDeq = clock();
	fordJohnsonMergeInsertionSort(intDeque, 0, intVec.size() - 1);
	clock_t endDeq = clock();
	std::cout << "After: ";
	printVec(intVec);
	double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000;
	double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000;
	std::cout << "Time to process a range of " << intVec.size() << " elements with std::vec container: " << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << intDeque.size() << " elements with std::deque container: " << timeDeq << " us" << std::endl;
	return 0;
}