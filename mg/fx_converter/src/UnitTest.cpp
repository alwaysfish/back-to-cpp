#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GRNN UnitTest
//#define BOOST_TEST_MODULE GRNN test suite 
#include <boost/test/unit_test.hpp>

using namespace std;

#include "ExchangeBoard.hpp"
#include "ExchangeRate.hpp"


BOOST_AUTO_TEST_CASE(corr_mon_test){

    unordered_map<string, unordered_map<string,shared_ptr<ExchangeRate>>> umap;

    BOOST_CHECK(insertExchange("/home/margon/projects/back-to-cpp/datasets/exchange_rates.csv", umap));

    BOOST_CHECK(umap["GBP"]["USD"] -> getAsk()==1.3701);
    BOOST_CHECK(umap["GBP"]["USD"] -> getBid()==1.373);

    BOOST_CHECK(converter(umap,"USD","USD",100)==0);

    BOOST_CHECK(converter(umap,"USD","GBP",0)==0);

    //BOOST_CHECK(corr_mon(umap,"GBP","SEK",200.5)!=0);

    
}
