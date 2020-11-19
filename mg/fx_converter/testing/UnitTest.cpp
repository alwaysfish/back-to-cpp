#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GRNN UnitTest
//#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>


using namespace std;

#include "../include/ExchangeBoard.hpp"
#include "../include/ExchangeRate.hpp"


BOOST_AUTO_TEST_CASE(file_test){

    nested_unord_map umap;

    BOOST_CHECK(insertCSV(umap));

    if(umap.empty())
    BOOST_FAIL("nested unordered map is empty");
    const std::string from="GBP";
    const std::string to="USD";


    BOOST_CHECK(isdigit(umap[from][to]->getBid())==true);
    BOOST_CHECK_EQUAL(umap[from][to]->getBid(),1.3701);


    

}

BOOST_AUTO_TEST_CASE(coverter_test){
    
    nested_unord_map umap;
    insertCSV(umap);
    const std::string from="GBP";
    const std::string to="USD";
    const double amount=100;    

    BOOST_CHECK(converter(umap,from,to,amount)==0);

    BOOST_CHECK(converter(umap,to,to,0)==0);
}
