#include "BitcoinExchange.hpp"

static void splitLine(const std::string& str, std::string& key, double &value, const char * delim) {
	char	*p;
	size_t delimPos = str.find(delim, 0);

	key = str.substr(0, delimPos);
	value = strtod(str.substr(delimPos + strlen(delim)).c_str(), &p);
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
	unsigned int year, month, day;
	size_t sep1 = key.find('-');
	size_t sep2 = key.find('-', sep1 + 1);
	if (sep1 == std::string::npos || sep2 == std::string::npos) throw key;
	std::string yearStr = key.substr(0, sep1);
	std::string monthStr = key.substr(sep1 + 1, sep2 - sep1 - 1);
	std::string dayStr = key.substr(sep2 + 1);
	if (!isNumber(yearStr) || !isNumber(monthStr) || !isNumber(dayStr)) throw key;
	year = (unsigned int)atoi(yearStr.c_str());
	month = (unsigned int)atoi(monthStr.c_str());
	day = (unsigned int)atoi(dayStr.c_str());
	if ((month < 1 || month > 12) || (day < 1 || day > 31)) throw key;

	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30) throw key;
	}

	if (month == 2) {
		bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
		if ((isLeapYear && day > 29) || (!isLeapYear && day > 28)) throw key;
	}

	if (isnan(value) || value < 0.0) throw value;
}

static void extractData(std::ifstream& dataStream, std::map< std::string, double >& data) {
	std::string		line;
	std::string		key;
	double			value;

	while (std::getline(dataStream, line)) {
		splitLine(line, key, value, ",");
		validateData(key, value);
		data[key] = value;
	}
}

static int validateKeys(const std::string&	keysString) {
	if (keysString == "date,exchange_rate")
		return SUCCES;
	if (keysString == "date | value")
		return SUCCES;
	return FAILURE;
}

int setupData(std::map< std::string, double >& data) {
	std::ifstream dataStream("data.csv");
	std::string line;

	if (!dataStream.good()) {
		std::cerr << "Couldnt open data file" << std::endl;
		return FAILURE;
	}
	std::getline(dataStream, line);
	if (validateKeys(line) != SUCCES)
		return FAILURE;
	try {
		extractData(dataStream, data);
	} catch (std::exception &e) {
		std::cerr << "Data error: " << e.what() << std::endl;
		return FAILURE;
	} catch (std::string& e) {
		std::cerr << "Data error: " << e << std::endl;
		return FAILURE;
	} catch (double& e) {
		std::cerr << "Data error: " << e << std::endl;
		return FAILURE;
	}
	return SUCCES;
}

static float getRate(const std::map<std::string, double>& data, const std::string& date) {
	std::map<std::string, double>::const_iterator it = data.lower_bound(date);

	if (it->first != date && it != data.begin()) {
		--it;
	}

	if (it != data.end()) {
		return it->second;
	} else if (!data.empty()) {
		return it->second;
	}
	return -1.0f;
}

int processInput(const char* inputPath, const std::map<std::string, double>& data) {
	std::ifstream	inputStream(inputPath);
	std::string		line;
	std::string		key;
	double			value;
	double			total;

	if (!inputStream.good()) {
		std::cerr << "Couldnt open input file" << std::endl;
		return FAILURE;
	}
	std::getline(inputStream, line);
	if (validateKeys(line) != SUCCES)
		return FAILURE;
	while (std::getline(inputStream, line)) {
		splitLine(line, key, value, " | ");
		try {
			validateData(key, value);
			if (value >= 1000.0) throw value;
			total = getRate(data, key) * value;
			std::cout << key << " => " << value << " = " << total << std::endl;
		} catch (std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
			return FAILURE;
		} catch (std::string& e) {
			std::cerr << "Error: " << "bad input => " << e << std::endl;
		} catch (double& e) {
			std::cerr << "Error: ";
			if (isnan(e))
				std::cerr << "not a number.";
			else if (e < 0.0)
				std::cerr << "not a positive number.";
			else if(e >= 1000.0)
				std::cerr << "too large a number.";
			std::cerr << std::endl;
		}
	}

	return SUCCES;
}
