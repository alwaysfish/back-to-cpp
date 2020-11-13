#include <fstream>
#include "exchange_rate.hpp"

using namespace std;


void ExchangeRate::update(double bid, double ask)
{
    if (bid != -1) m_bid = bid;
    if (ask != -1) m_ask = ask;
}

ExchangeRate & ExchangeRate::update_all(float change)
{
    m_bid += change;
    m_ask += change;
    m_last += change;

    return *this;
}

double ExchangeRate::convert_from(const string &from, double amount) const
{
    return amount * get_from_rate(from);
}

double ExchangeRate::convert_to(const string &to, double amount) const
{
    return amount * get_to_rate(to);
}

float ExchangeRate::get_from_rate(const string &from) const
{
    if (from == m_base)
        return m_bid;
    else if (from == m_quote)
        return 1 / m_ask;
    else return 0;
}

float ExchangeRate::get_to_rate(const string &to) const
{
    if (to == m_base)
        return 1 / m_ask;
    else if (to == m_quote)
        return m_bid;
    else return 0;
}

float ExchangeRate::get_from_quote(const string &from) const
{
    if (from == m_base)
        return m_bid;
    else if (from == m_quote)
        return m_ask;
    else return 0;
}

float ExchangeRate::get_to_quote(const string &to) const
{
    if (to == m_base)
        return m_ask;
    else if (to == m_quote)
        return m_bid;
    else return 0;
}
