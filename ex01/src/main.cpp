#include "RPN.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error: Usage Format: ./RPN \"expression\"\n";
		return 1;
	}

	RPN rpn;
	rpn.expresProcess(argv[1]);

	return 0;
}