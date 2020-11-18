#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "ExchangeRate.hpp"


typedef unordered_map<string, unordered_map<string,shared_ptr<ExchangeRate>>> nested_unord_map;

//Class to store exchange rate information from exchange_rates.csv
class ExchangeBoard{
    private:
        std::unordered_map<std::string, std::unordered_map<std::string,ExchangeRate>> exchangeRates;   
    public:
        ExchangeBoard() {}

};

//Conversion calculator finds out the exchange rate between the currency from to the exchanged currency- including any intermediate currencies
double const converter(nested_unord_map& umap, const std::string &_curr_from, const std::string &_curr_to, double &amount);


//find any intermediate currencies between the currency exchanged from and to
double check_intermed(nested_unord_map& umap, std::string const  &curr_from, std::string const &intermed, const std::string &curr_to, double &amount);
