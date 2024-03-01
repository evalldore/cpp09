#include "BitcoinExchange.hpp"

static void splitLine(const std::string& str, std::string& key, double &value) {
	char	*p;
	size_t delimPos = str.find(',', 0);

	key = str.substr(0, delimPos);
	value = strtod(str.substr(delimPos + 1).c_str(), &p);
	if (*p)
		value = NAN;
}

static bool isNumber(const std::string& str) {
	if (str.empty()) return false;

	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
		if (!isdigit(*it)) {
			return false;
		}
	}
	return true;
}

static void validateData(const std::string& key, const double& value) {
	size_t sep1 = key.find('-');
	size_t sep2 = key.find('-', sep1 + 1);
	if (sep1 == std::string::npos || sep2 == std::string::npos) throw InvalidDateException();
	std::string yearStr = key.substr(0, sep1);
	std::string monthStr = key.substr(sep1 + 1, sep2 - sep1 - 1);
	std::string dayStr = key.substr(sep2 + 1);
	if (!isNumber(yearStr) || !isNumber(monthStr) || !isNumber(dayStr)) throw InvalidDateException();
	if (isnan(value)) throw InvalidValueException();
}

static void extractData(std::fstream& dataStream, std::map< std::string, double >& data) {
	char	lineBuffer[BUFFER_SIZE];
	std::string key;
	double value;

	while (!dataStream.getline(lineBuffer, BUFFER_SIZE, '\n').eof()) {
		splitLine(lineBuffer, key, value);
		validateData(key, value);
		data[key] = value;
	}
}

static int validateKeys(const std::string&	keysString) {
	if (keysString == "date,exchange_rate")
		return SUCCES;
	return FAILURE;
}

int setupData(std::map< std::string, double >& data) {
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
	if (validateKeys(keysBuffer) != SUCCES)
		return FAILURE;
	try {
		extractData(dataStream, data);
	} catch (std::exception& e) {
		std::cerr << "EXCEPTION" << ' ' << e.what() << std::endl;
		return FAILURE;
	}
	return SUCCES;
}

const char* InvalidDateException::what(void) const throw() {
	return "Invalid date";
}

const char* InvalidValueException::what(void) const throw() {
	return "Invalid value";
}
