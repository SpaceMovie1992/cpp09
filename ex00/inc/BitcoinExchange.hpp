#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

class BitcoinExchange
{
private:
	std::map<std::string, double> data;

	void loadExchangeRates(const std::string &databaseFile);
	void calculateExchange(const std::string &date, double value);
	void processInputFile(const std::string &inputFile);

public:
	BitcoinExchange() = default;
	BitcoinExchange(const BitcoinExchange &other) = default;
	BitcoinExchange &operator=(const BitcoinExchange &other) = default;
	~BitcoinExchange() = default;
	
	void run(const std::string &inputFile);
	std::string trimWhitespace(const std::string& str);
};

bool isDateValid(const std::string& date);