/*
ExchangeBoard stores all exchange rates and allows to convert one currency to another.
There are two key attributes:
    m_rates: an unordered map that stores pointers to each ExchangeRate, loaded from a data file
    m_board: a 2-dimensional unordered map, which allows to quickly check what conversions are possible
        to do. First unordered map represents 'from' currency, and the second linked unordered_map represents
        'to' currency. The values of the second unordered_map are pointers to exchange rates.
*/

#ifndef EXCHANGE_BOARD_HPP
#define EXCHANGE_BOARD_HPP

#include <string>
#include <unordered_map>
#include <set>
#include <memory>
#include <mutex>
#include "exchange_rate.hpp"

/*

*/
struct Conversion
{
    string from;
    string to;
    double amount;
    double rate;
    double converted_amount;
    string pair;
    bool cross;
    string cross_ccy;

    Conversion(const string &from_, const string &to_, double amount_) : from{from_}, to{to_}, amount{amount_},
        rate{0}, converted_amount{0}, cross{false} {}
};


/* 
    ExchangeRateMap
        key - currency pair name, e.g., EUR/USD, USD/JPY
        value - pointer to ExchangeRate instance, that corresponds to the currency pair
*/
typedef std::unordered_map<std::string, std::shared_ptr<ExchangeRate>> ExchangeRateMap;

/*
    FromToExchangeMap: Maps from->to currency conversion relation and points to exchange rate to be used to do
    the conversion. 
        key1 - from currency, e.g., EUR, USD
        key2 - to currency, e.g., USD, JPY
        value - pointer to ExchangeRate instance that would be used to perform the conversion
*/

typedef std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<ExchangeRate>>> FromToExchangeMap;

// TODO: refactor the code to use only one map

typedef shared_ptr<ExchangeRate> ExchangeRatePtr;

class ExchangeBoard
{
private:
    std::mutex m_mutex;

    ExchangeRateMap m_rates;
    FromToExchangeMap m_board;

public:
    
    // Loads exchange rates from CSV file
    bool load_rates(const string &fname);

    /*
        Performs conversion.

        Returns: 
            true - if conversion was successful; conv will be filled with conversion details
            false - if conversion was unsuccessful
    */
    bool convert(Conversion &conv);

    // Returns pointer to ExchangeRate that corresponds to currency pair, e.g., EUR/USD, USD/JPY, etc.
    ExchangeRatePtr get_rate(const string &ccy_pair);

    // Updates all quotes (last, bid, ask) for a given currency pair, e.g., EUR/USD, USD/JPY, etc.
    void update_rate(const string &ccy_pair, double last);
};

#endif