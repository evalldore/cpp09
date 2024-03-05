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

int		setupData(std::map< std::string, double >&);
int		processInput(const char*, const std::map<std::string, double>&);