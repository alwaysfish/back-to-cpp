/* Converter.cpp is where the main application is run, delcaring variables and accepting
user input for which currency they want converted, as well as managing threads*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <functional>
#include <algorithm>
#include <cctype>

#include "currency.hpp"
#include "exchangeRate.hpp"
#include "exchangeBoard.hpp"
#include "randomWalk.hpp"

using namespace std;

string upperCase(string str);

int main()
{   
    string base;
    string quote;
    double amount;
    double convertedAmount;
    vector<Currency> currencies;
    ExchangeBoard exchangeBoard;
    atomic<bool> run_threads(true);
    
    thread thread1(change_rate, ref(run_threads));
    
    exchangeBoard.readExchangeRatesFromFile("/home/stephen/projects/back-to-cpp/datasets/exchange_rates.csv");
    readCurrenciesFromFile("/home/stephen/projects/back-to-cpp/datasets/currencies.csv", currencies);
    
    cout << "Enter the currency code (e.g. USD) you wish to trade: " << endl;
    cin >> base; transform(base.begin(), base.end(), base.begin(), ptr_fun<int, int>(toupper)); //change to uppercase
    cout << "Please enter the amount you wish to trade: " << endl;
    cin >> amount;
    cout << "Please enter the currency code (e.g. USD) you wish to convert to: " << endl;
    cin >> quote; transform(quote.begin(), quote.end(), quote.begin(), ptr_fun<int, int>(toupper));
    
    exchangeBoard.exchange(base, quote, amount);
   
    thread1.join();
    return 0;
}