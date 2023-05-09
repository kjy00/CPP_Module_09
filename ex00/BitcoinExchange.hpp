#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>
#include <map>

#define FILEOPEN_ERR "Error: could not open file."
#define INPUT_ERR "Error: bad input => "
#define TOOLARGEVALUE_ERR "Error: too large a number."
#define NOTPOSITIVE_ERR "Error: not a positive number."
#define NODATE_ERR "Error: no such date."

class BitcoinExchange
{
	private:
		std::map<std::string, float> _data;
		std::string _dataFilename;
		std::string _targetFilename;

		std::map<std::string, float> parseData(std::string filename);
		std::pair<std::string, float> parseTargetLine(std::string line);

		std::string checkValidDate(std::string date);
		float checkValidValue(std::string value);

		void printResult(std::pair<std::string, float> data);

	public:
		BitcoinExchange();
		BitcoinExchange(char *target, std::string data);
		BitcoinExchange(const BitcoinExchange &ref);
		BitcoinExchange &operator=(const BitcoinExchange &ref);
		~BitcoinExchange();

		void execute();
};

#endif
