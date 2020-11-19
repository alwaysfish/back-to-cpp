#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

#include "exchangeBoard.hpp"

vector<string> split(const string &stream, char delim);

void ExchangeBoard::readExchangeRatesFromFile(const string &fileName)
{
    ifstream file(fileName.c_str());
    string line;
    string key;
    vector<string> values;

    if (!file)
    {
        cout << "Cannot read from this file: " << fileName << endl;
    }

    //Skip first line 
    getline(file, line);

    while(getline(file, line))
    {
        values = split(line, ',');
        //Create a new ExchangeRate object wrapped in a shared_ptr
        auto pointerRate = make_shared<ExchangeRate>(values[0], values[1],
        stod(values[2]), stod(values[3]), stod(values[4]));

        key = pointerRate->getPair(); //Map key is concatination of the rate base+quote
        //Add each exchange rate to an exchangeRates unordered_map
        exchangeRates[key] = pointerRate;

        //Add each exchange to a nested unordered_map, key is base and quote, or quote and base
        exchangeBoard[pointerRate.get()->getBase()][pointerRate.get()->getQuote()] = pointerRate;
        exchangeBoard[pointerRate.get()->getQuote()][pointerRate.get()->getBase()] = pointerRate;
    }
}

vector<string> split(const string &stream, char delim)
{
    vector<string> result;
    stringstream ss(stream);
    string item;

    while (getline(ss, item, delim))
        result.push_back(item);
    return result;
}

double ExchangeBoard::exchange(const string &base, const string &quote, double amount)
{
    auto fromRate = exchangeBoard.find(base);
    auto toRate = exchangeBoard.find(quote);

    //Validating base and quote are valid currencies
    if(fromRate==exchangeBoard.end())
    {
        cout << "Currency " << base << " does not exist" << endl;
        return -1;
    }
    if(toRate==exchangeBoard.end())
    {
        cout << "Currency " << quote << " does not exist" << endl;
        return -1;
    }

    auto fromExch = fromRate->second.find(quote);
    //Calculate if no intermediary required
    if(fromExch != fromRate->second.end())
    {
        if(fromExch->second.get()->getBase()==base)
        {
            amount = amount * (fromExch->second.get()->getBid());
        }
        else
        {
            amount = amount * (1/fromExch->second.get()->getAsk());
        }
        
        cout << "Converted Amount: " << amount << " " << quote << endl;
    }

        //Find intermediary curriences based off the to rate and common base/quote values

        /* Needs some kind of search through each map to find the intermediary currency
        based on a common base/quote value between the two*/

        /*
        auto intermExch1 = toRate->second.find(fromRate->second.get()->getBase());
        auto intermExch2 = toRate->second.find(fromRate->second.get()->getQuote());
        fromRate->second.
        if(intermExch1 != toRate->second.end())
        {
            amount = amount * (intermExch2->second.get().getBid());
        }
        else if (intermExch2 != toRate->second.end())
        {
            amount = amount * (1/intermExch1->second.get().getAsk());
        }
        else if (intermExch2 == toRate->second.end() && intermExch1 == toRate->second.end())
        {
            cout << "Cannot make currency exchange" << endl;
            return -1;
        } 
        */
    return amount;
}