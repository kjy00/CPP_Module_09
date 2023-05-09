#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(char *target, std::string data) : _dataFilename(data), _targetFilename(target) {
	this->_data = parseData(_dataFilename);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &ref) {
	*this = ref;
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &ref) {
	if (this != &ref) {
		this->_data = ref._data;
		this->_dataFilename = ref._dataFilename;
		this->_targetFilename = ref._targetFilename;
	}
	return *this;
}

std::map<std::string, float> BitcoinExchange::parseData(std::string filename) {
	std::map<std::string, float> data;
	std::ifstream ifs;
	std::string buf;

	ifs.open(filename);
	if (!ifs) {
		std::cout << FILEOPEN_ERR << std::endl;
		exit (EXIT_FAILURE);
	}

	std::getline(ifs, buf);
	while (std::getline(ifs, buf)) {
		size_t pos = buf.find(",");
    std::string date = buf.substr(0, pos);
    std::string value = buf.substr(pos + 1);

		data[date] = std::strtof(value.c_str(), NULL);
	}

	ifs.close();
	return data;
}

std::pair<std::string, float> BitcoinExchange::parseTargetLine(std::string line) {
	size_t pos = line.find(" | ");

	if (pos == std::string::npos)
		throw std::invalid_argument(INPUT_ERR + line);

	std::string date = checkValidDate(line.substr(0, pos));
	float value = checkValidValue(line.substr(pos + 3));

	return std::pair<std::string, float>(date, value);
}

std::string BitcoinExchange::checkValidDate(std::string date) {
	std::stringstream ss(date, std::ios_base::in);
	int year, month, day;
	char sep;

	ss >> year >> sep >> month >> sep >> day;
	if (date.length() != 10 || ss.fail() || ss.get() != EOF || sep != '-')
		throw std::invalid_argument(INPUT_ERR + date);
	
	struct tm timeinfo;
	time_t t;

	memset(&timeinfo, 0, sizeof(struct tm));
	timeinfo.tm_year = year - 1900;
  timeinfo.tm_mon = month - 1;
  timeinfo.tm_mday = day;
	t = std::mktime(&timeinfo);

	if (t == -1 || timeinfo.tm_year != year - 1900 || timeinfo.tm_mon != month - 1 || timeinfo.tm_mday != day)
    throw std::invalid_argument(INPUT_ERR + date);

	return date;
}

float BitcoinExchange::checkValidValue(std::string value) {
	if (value.length() == 0)
		throw std::invalid_argument(INPUT_ERR + value);

	char* endptr;
	float fValue = std::strtof(value.c_str(), &endptr);

	if (*endptr != '\0')
		throw std::invalid_argument(INPUT_ERR + value);
	if (fValue > 1000)
		throw std::invalid_argument(TOOLARGEVALUE_ERR);
	if (fValue < 0)
		throw std::invalid_argument(NOTPOSITIVE_ERR);

	return fValue;
}

void BitcoinExchange::printResult(std::pair<std::string, float> data) {
	std::map<std::string, float>::iterator it = _data.lower_bound(data.first);

	if (it == _data.begin() && it->first != data.first)
    throw std::invalid_argument(NODATE_ERR);
  else if (it->first != data.first)
    it--;

	float result = it->second * data.second;

	std::cout << data.first << " => " << data.second << " = " << result << std::endl;
}

void BitcoinExchange::execute() {
	std::ifstream ifs;
	std::string buf;

	ifs.open(_targetFilename);
	if (!ifs) {
		std::cout << FILEOPEN_ERR << std::endl;
		exit (EXIT_FAILURE);
	}

	std::getline(ifs, buf);
	while (std::getline(ifs, buf)) {
		try {
			std::pair<std::string, float> data = parseTargetLine(buf);
			printResult(data);

		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}

	ifs.close();
}
