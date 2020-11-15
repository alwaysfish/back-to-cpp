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

class ExchangeBoard
{
private:
    std::mutex m_mutex;

    std::unordered_map<std::string, std::shared_ptr<ExchangeRate>> m_rates;
    std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<ExchangeRate>>> m_board;

public:
    
    bool load_rates(const string &fname);

    bool convert(Conversion &conv);

    shared_ptr<const ExchangeRate> get_rate(const string &ccy_pair);
    void update_rate(const string &ccy_pair, double last);
};

#endif