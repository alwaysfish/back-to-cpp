/*ExchangeRate class allows for the creation of ExchangeRate objects
via the readFromFile method in ExchangeBoard*/
#include <string>
#include <unordered_map>

#pragma once

using namespace std;

class ExchangeRate
{
    private:
        string base;
        string quote;
        double bid;
        double ask;
        double last;
        string curPair;

    private:
        inline void setCurPair() { curPair = base + quote; }
        
    public:
        ExchangeRate(): base{""}, quote{""}, bid{0}, ask{0}, last{0} {};
        ExchangeRate(const string& new_base, const string& new_quote, double new_bid, double new_ask, double new_last):
            base{new_base}, quote{new_quote}, bid{new_bid}, ask{new_ask}, last{new_last} {setCurPair(); }
        ~ExchangeRate() {}

        const string & getBase() const { return base; }
        const string & getQuote() const { return quote; }
        const double getBid() const { return bid; }
        const double getAsk() const { return ask; }
        const double getLast() const { return last; }
        string getPair() const { return curPair; }

};