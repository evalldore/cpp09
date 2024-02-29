#include "BitcoinExchange.hpp"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Invalid arguments, requires a filename" << std::endl;
		return 1;
	}
	std::fstream inputStream;
	inputStream.open(argv[1], std::fstream::in);
	if (!inputStream.good()) {
		std::cerr << "Couldnt open input file" << std::endl;
		return 1;
	}
	std::map< std::string, double > data;
	if (setupData(data) != 0) {
		std::cerr << "Setting up data failure!" << std::endl;
		return 1;
	}
}