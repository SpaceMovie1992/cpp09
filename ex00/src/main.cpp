#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Invalid number of arguments. Please provide an input file." << std::endl;
		std::cerr << "Usage: ./btc [input file]" << std::endl;
		return EXIT_FAILURE;
	}

	try
	{
		BitcoinExchange exchange;
		exchange.run(argv[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
