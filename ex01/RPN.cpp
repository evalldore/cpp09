#include "RPN.hpp"

static bool isNumber(const std::string& str) {
	if (str.empty()) return false;
	std::string::const_iterator it = str.begin();
	while (it != str.end() && std::isdigit(*it)) it++;
	return (it == str.end());
}

static bool operate(const std::string& str, std::stack<int>& stack) {
	if (stack.size() < 2) {
		std::cout << "Invalid amount of operands" << std::endl;
		return false;
	}
	if (str.length() > 1) {
		std::cout << "Invalid operator: " << str << std::endl;
		return false;
	}
	int elements[2];
	elements[0] = stack.top();
	stack.pop();
	elements[1] = stack.top();
	stack.pop();
	switch (str[0]) {
		case '+':
			stack.push(elements[1] + elements[0]);
			return true;
		case '-':
			stack.push(elements[1] - elements[0]);
			return true;
		case '/':
			if (elements[0] == 0)
				return false;
			stack.push(elements[1] / elements[0]);
			return true;
		case '*':
			stack.push(elements[1] * elements[0]);
			return true;
		default:
			std::cout << "Invalid operator: " << str[0] << std::endl;
	}
	return false;
}

bool calc(const std::string str) {
	std::stack<int> stack;
	std::stringstream ssin(str);
	std::string token;

	while (ssin.good()) {
		ssin >> token;
		if (isNumber(token))
			stack.push(std::atoi(token.c_str()));
		else
			if (!operate(token, stack))
				return false;
	}
	if (stack.size() > 1) {
		std::cout << "Stack isnt fully processed!" << std::endl;
	}
	std::cout << stack.top() << std::endl;
	return true;
}