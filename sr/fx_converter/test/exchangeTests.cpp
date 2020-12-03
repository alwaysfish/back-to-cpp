#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GRNN test suite
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <vector>
#include <iostream>

#include "currencyList.hpp"
#include "exchangeBoard.hpp"

BOOST_AUTO_TEST_CASE(testThatCurrenciesAreReadFromFile)
{
    vector<Currency> currencies;
    currencies = readCurrenciesFromFile("/home/stephen/projects/back-to-cpp/datasets/currencies.csv");
    BOOST_CHECK_EQUAL(currencies.size(), 81); //hardcoded, change to variable later
}


BOOST_AUTO_TEST_CASE(testThatAValidBaseMustBeEntered)
{
    ExchangeBoard exchangeBoard;
    exchangeBoard.readExchangeRatesFromFile("/home/stephen/projects/back-to-cpp/datasets/exchange_rates.csv");
    double convertedAmount = exchangeBoard.exchange("UDS", "GBP", 0);
    BOOST_CHECK(convertedAmount == -1);
}

BOOST_AUTO_TEST_CASE(testThatAValidQuoteMustBeEntered)
{
    ExchangeBoard exchangeBoard;
    exchangeBoard.readExchangeRatesFromFile("/home/stephen/projects/back-to-cpp/datasets/exchange_rates.csv");
    double convertedAmount = exchangeBoard.exchange("USD", "GP", 0);
    BOOST_CHECK(convertedAmount == -1);
}   

BOOST_AUTO_TEST_CASE(testThatADirectConversionCanBeMade)
{
    ExchangeBoard exchangeBoard;
    exchangeBoard.readExchangeRatesFromFile("/home/stephen/projects/back-to-cpp/datasets/exchange_rates.csv");
    double convertedAmount = exchangeBoard.exchange("GBP", "USD", 100); 
    double expectedAmount = 100*1.3701; //hardcoded, change to amount*find->second.getBid
    BOOST_CHECK(convertedAmount == expectedAmount);
}


//testThatAnIntermediaryConversionCanBeMade
//testThatExchangeRatesCanBeReadFromFile
