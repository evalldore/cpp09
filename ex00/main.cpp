#include "BitcoinExchange.hpp"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Invalid arguments, requires a filename" << std::endl;
		return 1;
	}
	std::map< std::string, double > data;
	if (setupData(data) != SUCCES) {
		std::cerr << "Setting up data failure!" << std::endl;
		return 1;
	}
	if (processInput(argv[1], data) != SUCCES) {
		std::cerr << "Processing input failure" << std::endl;
		return 1;
	}
	return 0;
}