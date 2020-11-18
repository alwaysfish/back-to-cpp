#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
//## Class __ExchangeRate__

//Attributes:

//- from currency
//- to currency
//- rate

class ExchangeRate{
    private:
        std::string base;
        std::string quote;
        double bid=0;
        double ask=0;
        double last=0;

    public:
        ExchangeRate() {}
         //~ExchangeRate();

    /*ExchangeRate(std::string new_base, std::string new_quote, double new_bid, double new_ask, double new_last){
            base= new_base;
            quote= new_quote;
            bid= new_bid;
            ask= new_ask;
            last= new_last;
    }*/

    /*ExchangeRate::ExchangeRate(){
        delete base;
        delete quote;
        delete bid;
        delete ask;
        delete last;
    }
*/
    const std::string & getBase () const {
        return base;
    }

    void setBase(std::string new_base){
        base=new_base;
    }


    const std::string & getQuote () const {
        return quote;
    }

    void setQuote(std::string new_quote){
        quote=new_quote;
    }


    const double & getBid () const {

        return bid;
    }

    void setBid(double new_bid){
        bid=new_bid;
    }


    const double & getAsk () const {
        return ask;
    }

    void setAsk(double new_ask){
       ask=new_ask;
    }


    const double & getLast () const {
        return last;
    }

    void setLast(double new_last){
       last=new_last;
    }
};

typedef std::unordered_map<std::string, std::unordered_map<std::string,std::shared_ptr<ExchangeRate>>> nested_unord_map;

bool const insertCSV(nested_unord_map &umap);
