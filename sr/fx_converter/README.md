# README fx_converter application

## Project Overview:
- Allow the user to input an amount and two currency codes to do a currency exchange between any currency
- Read currency and exchange rate data from files and store them in objects
- Implement multithreading for a constant random generation of exchange rates and updating those rates in the table

## Installs:
- CMake - sudo apt-get install cmake
- Boost - sudo apt-get install libboost-all-dev

### CMake
Use the following commands once changes are made
- cmake .
- make

## Main Files:
currencyList - Contains the Currency class responsible for creating Currency objects that are stored in a currencies vector
via the readCurrencyFromFile function

exchangeRate - Contains the ExchangeRate class responsible for creating exchange rate objects that are stored in an exchangeRate
map and exchangeBoard nested map

exchangeBoard - Contains the ExchangeBoard class responsible for creating the exchangeRate and exchangeBoard maps to store our 
exchange rates, also contains the functions for readExchangeRatesFromFile and exchange for carrying out the exchange logic

randomWalk - Contains the functions for what the currency generation thread will do via the change_rate function. The rate is randomly generated
using the previous rate multiplied by a random negative or positive value, and updated randomly every 2-5 seconds.


## Testing:
-This project makes use of Boost unit testing

### Files:
exchangeTests: Contains all tests for this project, testing reading from file, searching for exchangeRates, and performing an exchange