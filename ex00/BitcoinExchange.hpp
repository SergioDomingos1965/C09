#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange 
{
private:
  std::map<std::string, double> _database;
  void loadDatabase();
  bool validDate(const std::string &date);
  double getRate(const std::string &date);
public:
  BitcoinExchange();
  BitcoinExchange(const BitcoinExchange &other);
  BitcoinExchange &operator=(const BitcoinExchange &other);
  ~BitcoinExchange();
  void processInput(const std::string &filename);
};

#endif
