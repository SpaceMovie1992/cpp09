#include "BitcoinExchange.hpp"

void BitcoinExchange::loadExchangeRates(const std::string &databaseFile)
{
	std::ifstream file(databaseFile);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open database file");
	}

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		try
		{
			std::istringstream lineStream(line);
			std::string date, strValue;
			if (line.find(',') == std::string::npos)
			{
				throw std::runtime_error("bad input => " + line);
			}
			if (std::getline(lineStream, date, ',') && std::getline(lineStream, strValue))
			{
				if (date.empty() || strValue.empty())
				{
					throw std::runtime_error("empty date or value");
				}
				double bitcoinPrice = std::stod(strValue);
				if (bitcoinPrice < 0)
				{
					throw std::out_of_range("");
				}
				if (!isDateValid(date))
				{
					throw std::runtime_error("bad input => " + date);
				}
				this->data[date] = bitcoinPrice;
			}
			else
			{
				throw std::runtime_error("bad input => " + line);
			}
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
}

void BitcoinExchange::calculateExchange(const std::string &inputDate, double value)
{
	auto dateIterator = this->data.lower_bound(inputDate);

	if (dateIterator == this->data.end() || dateIterator->first != inputDate)
	{
		if (dateIterator == this->data.begin())
		{
			throw std::runtime_error("No date before " + inputDate);
		}
		dateIterator--;
	}
	double exchangeRate = value * dateIterator->second;
	std::cout << inputDate << " => " << value << " = " << exchangeRate << std::endl;
}

void BitcoinExchange::processInputFile(const std::string& inputFile) {
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open input file");
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        try {
            std::istringstream lineStream(line);
            std::string date, strValue;
            if (line.find('|') == std::string::npos) {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }
            if (std::getline(lineStream, date, '|') && std::getline(lineStream, strValue)) {
                date = trimWhitespace(date);
                strValue = trimWhitespace(strValue);
                if (date.empty() || strValue.empty()) {
                    std::cerr << "Error: empty date or value => " << line << std::endl;
                    continue;
                }
                double value;
                try {
                    value = std::stod(strValue);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: bad number => " << strValue << std::endl;
                    continue;
                }
                if (value < 0 || value > 1000) {
                    std::cerr << "Error: bad number => " << strValue << std::endl;
                    continue;
                }
                if (!isDateValid(date)) {
                    std::cerr << "Error: bad input => " << date << std::endl;
                    continue;
                }
                calculateExchange(date, value);
            } else {
                std::cerr << "Error: bad input => " << line << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

void BitcoinExchange::run(const std::string &inputFile)
{
	loadExchangeRates("data.csv");
	processInputFile(inputFile);
}

bool isDateValid(const std::string &date)
{
	int year, month, day;
	char dash1, dash2;

	std::istringstream dateStream(date);
	dateStream >> year >> dash1 >> month >> dash2 >> day;

	if (date.length() != 10 || dateStream.fail() || dash1 != '-' || dash2 != '-')
	{
		return false;
	}

	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
	{
		return false;
	}
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
	{
		return false;
	}
	if (month == 2)
	{
		bool isLeapYear = (year % 4 == 0 && (year % 100 != 0)) || (year % 400 == 0);
		if (day > 29 || (day > 28 && !isLeapYear))
		{
			return false;
		}
	}
	return true;
}

std::string BitcoinExchange::trimWhitespace(const std::string &str)
{
	const auto strBegin = str.find_first_not_of(" \t");
	if (strBegin == std::string::npos)
	{
		return "";
	}
	const auto strEnd = str.find_last_not_of(" \t");
	const auto strRange = strEnd - strBegin + 1;
	return str.substr(strBegin, strRange);
}
