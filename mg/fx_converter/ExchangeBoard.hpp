#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "ExchangeRate.hpp"

//## Class __ExchangeBoard__

//- list of ExchangeRates
//- does the exchange

class ExchangeBoard{
    private:
        unordered_map<string, unordered_map<string,ExchangeRate>> exchangeRates;   
    public:
        bool didExchange=false;
        ExchangeBoard() {}

};
double const corr_mon(unordered_map<string, unordered_map<string,shared_ptr<ExchangeRate>>>& umap, const string &_curr_from, const string &_curr_to, const double &amount);
double conversion_intermed(unordered_map<string, unordered_map<string,shared_ptr<ExchangeRate>>>& umap, const string &curr_from, const string &intermed, const string &curr_to, const double &amount);
