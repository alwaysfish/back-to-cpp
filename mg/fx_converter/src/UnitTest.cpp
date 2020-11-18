#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GRNN UnitTest
#include <boost/test/unit_test.hpp>

using namespace std;

#include "../include/ExchangeBoard.hpp"
#include "../include/ExchangeRate.hpp"


BOOST_AUTO_TEST_CASE(file_test){

    nested_unord_map umap;

    BOOST_CHECK(insertCSV(umap));

    if(umap.empty())
    BOOST_FAIL("nested unordered map is empty");
    
    BOOST_CHECK_EQUAL(umap["GBP"]["USD"]->getBid(),1.3701);


}

BOOST_AUTO_TEST_CASE(coverter_test){
    
    nested_unord_map umap;
    insertCSV(umap);

    BOOST_CHECK(converter(umap,"USD","USD",100)==0);

    BOOST_CHECK(converter(umap,"USD","GBP",0)==0);
}
