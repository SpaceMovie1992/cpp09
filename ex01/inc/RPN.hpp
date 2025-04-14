#pragma once

#include <iostream>
#include <sstream>
#include <stack>

class RPN
{
private:
	std::stack<int> stack;

public:
	RPN() = default;
	RPN(const RPN &other) = default;
	RPN &operator=(const RPN &other) = default;
	~RPN() = default;

	void expresProcess(const std::string &exp);
};