/* Converter.cpp is where the main application is run, delcaring variables and accepting
user input for file paths, which currency they want converted, 
as well as starting a thread for updating the exchange rates randomly*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <functional>
#include <algorithm>
#include <cctype>

#include "exchangeRate.hpp"
#include "exchangeBoard.hpp"
#include "randomWalk.hpp"
#include "currencyList.hpp"

using namespace std;

string upperCase(string str);

int main()
{   
    atomic<bool> run_threads(true);
    
    //Thread that randomly changes the price of exchange rates over 15 seconds
    //thread thread1(change_rate, ref(run_threads));
    
    ExchangeBoard exchangeBoard;
    vector<Currency> currencies;

    string filePath;
    cout << "Please enter the file path for exchange rates." << endl;
    cin >> filePath;
    exchangeBoard.readExchangeRatesFromFile(filePath);
    cout << "Please enter the file path for currencies." << endl;
    cin >> filePath;
    currencies = readCurrenciesFromFile(filePath);
    
    string base;
    string quote;
    double amount;
    double convertedAmount;

    cout << "Enter the currency code (e.g. USD) you wish to trade: " << endl;
    cin >> base; transform(base.begin(), base.end(), base.begin(), ptr_fun<int, int>(toupper)); //change to uppercase
    cout << "Please enter the amount you wish to trade: " << endl;
    cin >> amount;
    cout << "Please enter the currency code (e.g. USD) you wish to convert to: " << endl;
    cin >> quote; transform(quote.begin(), quote.end(), quote.begin(), ptr_fun<int, int>(toupper));
    
    exchangeBoard.exchange(base, quote, amount);
   
    //thread1.join();
    return 0;
}