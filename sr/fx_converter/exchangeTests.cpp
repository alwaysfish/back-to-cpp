#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GRNN test suite
#include <boost/test/unit_test.hpp>
#include <vector>

#include "currency.cpp"
#include "exchangeBoard.hpp"

BOOST_AUTO_TEST_CASE(testThatCurrenciesAreReadFromFile)
{
    vector<Currency> currencies;
    readCurrenciesFromFile("/home/stephen/projects/back-to-cpp/datasets/currencies.csv", currencies);
    BOOST_CHECK_EQUAL(currencies.size(), 81); //hardcoded, change to variable later
}

//testThatExchangeRatesCanBeReadFromFile

//testThatAValidBaseMustBeEntered
//testThatAValidQuoteMustBeEntered

//testThatADirectConversionCanBeMade
//testThatAnIntermediaryConversionCanBeMade

