#include <iostream>
#include <cstdlib>
#include "PmergeMe.hpp"

static bool init(std::vector<int>& vec, int argc, char *argv[]) {
	int		value;
	char	*end;
	for (int index = 1; index < argc; index++) {
		value = static_cast<int>(strtol(argv[index], &end, 10));
		if (*end || value < 0)
			return false;
		vec.push_back(value);
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
	if (!init(intVec, argc, argv)) {
		std::cerr << "Error: Invalid parameters" << std::endl;
		return 1;
	}
	std::cout << "Before: ";
	printVec(intVec);
	fordJohnsonMergeInsertionSort(intVec, 0, intVec.size() - 1);
	std::cout << "After: ";
	printVec(intVec);
	return 0;
}