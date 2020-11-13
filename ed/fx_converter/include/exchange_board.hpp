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

    Conversion(const string &from_, const string &to_, double amount_) : from{from_}, to{to_}, amount{amount_} {}
};

class ExchangeBoard
{
private:
    std::mutex m_mutex;

    std::unordered_map<std::string, std::shared_ptr<ExchangeRate>> m_rates;
    std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<ExchangeRate>>> m_board;
    //std::unordered_map<std::string, std::set<std::string>> m_board;

public:
    
    bool load_rates(const string &fname);

    bool convert(Conversion &conv);

    shared_ptr<const ExchangeRate> get_rate(const string &ccy_pair);
    void update_rate(const string &ccy_pair, double last);
};

#endif