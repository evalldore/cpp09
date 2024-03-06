#include <iostream>
#include "RPN.hpp"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Not enough arguments!" << std::endl;
		return 1;
	}
	if (!calc(argv[1]))
		std::cout << "Failed operation!" << std::endl;
}