#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <exception>
#include <map>
#include <cmath>
#include <sstream>
#include <exception>
#include <cctype>
#define SUCCES 0
#define FAILURE 1
#define INVALID_DATE 2
#define INVALID_VALUE 3
#define BUFFER_SIZE 256

class InvalidDateException : public std::exception {
	public:
		virtual const char* what(void) const throw();
};

class InvalidValueException : public std::exception {
	public:
		virtual const char* what(void) const throw();
};

int setupData(std::map< std::string, double >& data);