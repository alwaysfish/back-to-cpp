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
    if (from == m_base)
        return amount * m_bid;
    else if (from == m_quote)
        return amount / m_ask;
    else return -1;
}

double ExchangeRate::convert_to(const string &to, double amount) const
{
    if (to == m_base)
        return amount / m_ask;
    else if (to == m_quote)
        return amount * m_bid;
    else return -1;
}
