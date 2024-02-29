#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <exception>
#include <map>
#include <cmath>
#define SUCCES 0
#define FAILURE 1
#define BUFFER_SIZE 256

static void splitLine(const std::string& str, std::string& key, double &value) {
	char	*p;
	size_t delimPos = str.find(',', 0);

	key = str.substr(0, delimPos);
	value = strtod(str.substr(delimPos).c_str(), &p);
	if (*p)
		value = NAN;
}

static void extractData(std::fstream& dataStream, std::map< std::string, std::vector<double> >& data) {
	(void)data;
	char	lineBuffer[BUFFER_SIZE];
	std::string key;
	double value;

	while (!dataStream.getline(lineBuffer, BUFFER_SIZE, '\n').eof()) {
		splitLine(lineBuffer, key, value);
		std::cout << key << value << std::endl;
	}
}

static int validateKeys(const std::string&	keysString) {
	if (keysString == "date,exchange_rate\n")
		return SUCCES;
	return FAILURE;
}

static int setupData(std::map< std::string, std::vector<double> >& data) {
	(void)data;
	std::fstream dataStream;
	dataStream.open("data.csv", std::fstream::in);
	if (!dataStream.good()) {
		std::cerr << "Couldnt open data file" << std::endl;
		return FAILURE;
	}
	char keysBuffer[BUFFER_SIZE];
	std::vector<std::string> keysVec;

	if (dataStream.getline(keysBuffer, BUFFER_SIZE, '\n').eof())
		return FAILURE;
	if (validateKeys(keysBuffer) == FAILURE)
		return FAILURE;
	try {
		extractData(dataStream, data);
	} catch (std::exception& e) {
		std::cerr << "EXCEPTION" << e.what() << std::endl;
		return FAILURE;
	}
	return SUCCES;
}

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
	std::map< std::string, std::vector<double> > data;
	if (setupData(data) != 0) {
		std::cerr << "Setting up data failure!" << std::endl;
		return 1;
	}
}