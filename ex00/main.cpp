#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <map>
#define SUCCES 0
#define FAILURE 1
#define LINE_BUFFER 256

static void extractKeys(const std::string& keysBuffer, std::vector<std::string>& keysList) {
	size_t		pos = 0;

	while(true) {
		size_t delimPos = keysBuffer.find(',', pos);
		if (delimPos == std::string::npos) {
			keysList.push_back(keysBuffer.substr(pos, keysBuffer.find('\n')));
			break;
		}
		keysList.push_back(keysBuffer.substr(pos, delimPos));
		pos = delimPos + 1;
	}
}

static int validateKeys(std::vector<std::string>&	keysList) {
	if (keysList.size() > 2) return FAILURE;
	if (keysList[0] == "date" && keysList[1] == "exchange_rate")
		return (SUCCES);
	return (FAILURE);
}

static int setupData(std::map< std::string, std::vector<float> >& data) {
	(void)data;
	std::fstream dataStream;
	dataStream.open("data.csv", std::fstream::in);
	if (!dataStream.good()) {
		std::cerr << "Couldnt open data file" << std::endl;
		return FAILURE;
	}
	char					keysBuffer[LINE_BUFFER];
	std::vector<std::string>	keysVec;

	dataStream.getline(keysBuffer, LINE_BUFFER, '\n');
	try {
		extractKeys(keysBuffer, keysVec);
	} catch (std::exception& e) {
		std::cout << "EXCEPTION" << e.what() << std::endl;
		return FAILURE;
	}
	if (validateKeys(keysVec) == FAILURE)
		return FAILURE;
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
	std::map< std::string, std::vector<float> > data;
	if (setupData(data) != 0) {
		std::cerr << "Setting up data failure!" << std::endl;
		return 1;
	}
}