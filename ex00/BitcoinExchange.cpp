#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

BitcoinExchange::BitcoinExchange() { loadDatabase(); }

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
    : _database(other._database) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
  if (this != &other)
    _database = other._database;
  return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase() {
  std::ifstream file("data.csv");

  if (!file)
    throw std::runtime_error("Error: could not open database.");

  std::string line;
  std::getline(file, line);

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string date;
    std::string rate;

    std::getline(ss, date, ',');
    std::getline(ss, rate);

    _database[date] = std::atof(rate.c_str());
  }
}

bool BitcoinExchange::validDate(const std::string &date) {
  if (date.length() != 10)
    return false;

  if (date[4] != '-' || date[7] != '-')
    return false;

  int year = std::atoi(date.substr(0, 4).c_str());
  int month = std::atoi(date.substr(5, 2).c_str());
  int day = std::atoi(date.substr(8, 2).c_str());
  int f =  std::atoi(date.substr(5, 2).c_str());

  if (month < 1 || month > 12)
    return false;
  if(f == 2 && day > 28)
    return false;
  if (day < 1 || day > 31)
    return false;

  (void)year;
  return true;
}

double BitcoinExchange::getRate(const std::string &date) {
  std::map<std::string, double>::iterator it = _database.lower_bound(date);

  if (it == _database.end()) {
    it--;
    return it->second;
  }

  if (it->first != date) {
    if (it == _database.begin())
      throw std::runtime_error("Error: no earlier data.");
    it--;
  }

  return it->second;
}

bool BitcoinExchange::is_space(const std::string &str)
{
    size_t start = 0;
    size_t end = str.length();

    while(start < end && isspace(str[start]))
      start++;
    while(end > start && isspace(str[start]))
      end--;
    while(start < end)
    {
        if(isspace(str[start]))
          return true;
      start++;
    }
    return false;
}
void BitcoinExchange::processInput(const std::string &filename) {
  std::ifstream file(filename.c_str());
  if (!file)
    throw std::runtime_error("Error: could not open file.");

  std::string line;
  std::getline(file, line);
  if(line.find("date | value") == std::string::npos)
      throw std::runtime_error("Bad file");
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string date;
    std::string valueStr;

    if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr)) {
      std::cout << "Error: bad input => " << line << std::endl;
      continue;
    }

    while (date[date.size() - 1] == ' ')
      date.erase(date.size() - 1);

    while (valueStr[0] == ' ')
      valueStr.erase(0, 1);
    if (!validDate(date)) {
      std::cout << "Error: bad input => " << line << std::endl;
      continue;
    }
    if(is_space(valueStr))
    {
      std::cout << "Error: invalid number." << std::endl;
      continue;
    }
    double value = std::atof(valueStr.c_str());

    if (value < 0) {
      std::cout << "Error: not a positive number." << std::endl;
      continue;
    }

    if (value > 1000) {
      std::cout << "Error: too large a number." << std::endl;
      continue;
    }

    try {
      double rate = getRate(date);
      std::cout << date << " => " << value << " = " << value * rate
                << std::endl;
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }
}
