#include <iostream>
#include <cstdlib>
#include "PmergeMe.hpp"

static bool init(std::vector<int>& vec, int argc, char *argv[]) {
	int		value;
	char	*end;
	for (int index = 1; index < argc; index++) {
		value = static_cast<int>(strtol(argv[index], &end, 10));
		if (*end)
			return false;
		vec.push_back(value);
	}
	return true;
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		std::cerr << "Not enough arguments in parameters!" << std::endl;
		return 1;
	}
		
	std::vector<int> intVec;
	if (!init(intVec, argc, argv)) {
		std::cerr << "Invalid parameters to initialize int vector!" << std::endl;
		return 1;
	}
	mergeInsertionSort(intVec);
	return 0;
}