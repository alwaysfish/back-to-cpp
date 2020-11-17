#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
using namespace std;
//## Class __ExchangeRate__

//Attributes:

//- from currency
//- to currency
//- rate

class ExchangeRate{
    private:
        string base;
        string quote;
        double bid;
        double ask;
        double last;

    public:
        ExchangeRate() {}
         //~ExchangeRate();

    ExchangeRate(string new_base, string new_quote, double new_bid, double new_ask, double new_last){
            base= new_base;
            quote= new_quote;
            bid= new_bid;
            ask= new_ask;
            last= new_last;
    }

    /*ExchangeRate::ExchangeRate(){
        delete base;
        delete quote;
        delete bid;
        delete ask;
        delete last;
    }
*/
    const string & getBase () const {
        return base;
    }

    void setBase(string new_base){
        base=new_base;
    }


    const string & getQuote () const {
        return quote;
    }

    void setQuote(string new_quote){
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

bool const getExchange(const string fileName,  unordered_map<string, unordered_map<string,shared_ptr<ExchangeRate>>> &umap);
