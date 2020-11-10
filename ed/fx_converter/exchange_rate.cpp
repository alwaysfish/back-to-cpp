#include <fstream>
#include "exchange_rate.hpp"

using namespace std;


double ExchangeRate::buy(double amount)
{
    return amount * m_ask;
}
    
double ExchangeRate::sell(double amount)
{
    return amount * m_bid;
}

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