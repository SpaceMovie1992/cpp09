#include "RPN.hpp"

void RPN::expresProcess(const std::string &exp)
{
	std::istringstream iss(exp);
	std::string token;

	while (iss >> token)
	{
		if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (stack.size() < 2)
			{
				std::cerr << "Error: Operands insufficient\n";
				return;
			}

			int operand2 = stack.top();
			stack.pop();
			int operand1 = stack.top();
			stack.pop();

			int result;
			if (token == "+")
				result = operand1 + operand2;
			else if (token == "-")
				result = operand1 - operand2;
			else if (token == "*")
				result = operand1 * operand2;
			else if (token == "/")
			{
				if (operand2 == 0)
				{
					std::cerr << "Error: Division by zero\n";
					return;
				}
				result = operand1 / operand2;
			}

			stack.push(result);
		}
		else
		{
			try
			{
				int value = std::stoi(token);
				stack.push(value);
			}
			catch (const std::invalid_argument &e)
			{
				std::cerr << "Error: Invalid token\n";
				return;
			}
		}
	}

	if (stack.size() != 1)
	{
		std::cerr << "Error: Invalid RPN expression\n";
		return;
	}

	std::cout << stack.top() << std::endl;
}
