#ifndef EXCHANGE_RATE_HPP
#define EXCHANGE_RATE_HPP

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class ExchangeRate
{
private:
    string m_base;
    string m_quote;
    string m_pair_name;
    float m_bid;
    float m_ask;
    float m_last;

private:
    inline void set_pair_name() { m_pair_name = m_base + "/" + m_quote; }

public:
    ExchangeRate() {}
    ExchangeRate(const string& base, const string& quote) : m_base{base}, m_quote{quote} { set_pair_name(); }
    ExchangeRate(const string& base, const string& quote, float bid, float ask, float last) :
        m_base{base}, m_quote{quote}, m_bid{bid}, m_ask{ask}, m_last{last} { set_pair_name(); }
    ~ExchangeRate() {}

    const string& base() const { return m_base; }
    const string& quote() const { return m_quote; }
    string pair_name() const { return m_pair_name; };
    
    float get_bid() const { return m_bid; }
    float get_ask() const { return m_ask; }
    float get_last() const { return m_last; }

    double convert_from(const string &from, double amount) const;
    double convert_to(const string &to, double amount) const;
    
    double buy(double amount) const { return amount * m_ask; }
    double sell(double amount) const { return amount * m_bid; }

    // If -1 is passed, then the corresponding quote is not updated
    void update(double bid = -1, double ask = -1);
    ExchangeRate & update_all(float d);
};

#endif