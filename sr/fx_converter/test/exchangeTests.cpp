#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GRNN test suite
#include <boost/test/unit_test.hpp>
#include <vector>

#include "currencyList.hpp"
#include "exchangeBoard.hpp"
/*
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
    double convertedAmount = exchangeBoard.exchange("UDS", "GBP", 0); //Incorrect base returns amount + error
    BOOST_CHECK(convertedAmount == 0.0);
}

BOOST_AUTO_TEST_CASE(testThatAValidQuoteMustBeEntered)
{
    ExchangeBoard exchangeBoard;
    exchangeBoard.readExchangeRatesFromFile("/home/stephen/projects/back-to-cpp/datasets/exchange_rates.csv");
    double convertedAmount = exchangeBoard.exchange("USD", "GP", 0); //Incorrect quote returns amount + error
    BOOST_CHECK(convertedAmount == 0.0);
}   

BOOST_AUTO_TEST_CASE(testThatADirectConversionCanBeMade)
{
    ExchangeBoard exchangeBoard;
    exchangeBoard.readExchangeRatesFromFile("/home/stephen/projects/back-to-cpp/datasets/exchange_rates.csv");
    double convertedAmount = exchangeBoard.exchange("GBP", "USD", 100); 
    BOOST_CHECK(convertedAmount == 137.01);
}
*/

BOOST_AUTO_TEST_CASE(test1)
{
    BOOST_CHECK_EQUAL(1,1);
}
//testThatAnIntermediaryConversionCanBeMade
//testThatExchangeRatesCanBeReadFromFile
