#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "ExchangeRate.hpp"

//Class to store exchange rate information from exchange_rates.csv
class ExchangeBoard{
    private:
        nested_unord_map exchangeRates;   
    public:
        ExchangeBoard() {}

};

//Conversion calculator finds out the exchange rate between the currency from to the exchanged currency- including any intermediate currencies
double const converter(nested_unord_map& umap, const std::string &_curr_from, const std::string &_curr_to, const double amount);


//find any intermediate currencies between the currency exchanged from and to
double check_intermed(nested_unord_map& umap, std::string const  &curr_from, std::string const &intermed, const std::string &curr_to, const double amount);
