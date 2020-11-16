/*ExchangeBoard class reads data from a CSV file, creating Exchange Rate objects
and storing them in two maps which are used to perform a currency exchange
with or without an intermediary value*/

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "exchangeRate.hpp"

using namespace std;

class ExchangeBoard
{
    private: 
        unordered_map<string, shared_ptr<ExchangeRate>> exchangeRates;
        unordered_map<string, unordered_map<string, shared_ptr<ExchangeRate>>> exchangeBoard;

    public:
        void readExchangeRatesFromFile(const string &fileNames);
        double exchange(const string &base, const string &quote, double amount);
};
    
    
    