#include <iostream>
using namespace std;

#include "Currency.hpp"
#include "ExchangeBoard.hpp"
#include "ExchangeRate.hpp"
#include "RandomWalk.hpp"
#include "Updater.hpp"


int main(){
    
    double amount;
    string  curr_from;
    string curr_to;
    vector <Currency> currencies; 
    unordered_map<string, unordered_map<string,shared_ptr<ExchangeRate>>> umap;

//- loads currencies information from a CSV file
//- loads exchange rates from a CSV file 
 
    //getFileContent("  /home/margon/projects/back-to-cpp/datasets/currencies.csv",currencies);
    getExchange("/home/margon/projects/back-to-cpp/datasets/exchange_rates.csv", umap);


//- asks for amount and currency to exchange from
    cout<<"How much money out?\n";
    //cin>> mon;
    amount=50.5;
    
    cout<<"Which currency to exchange from?\n";
    //cin>> curr_from;
    curr_from="USD";
//- asks for currency to exchange to
    
    cout<<"Which currency to exchange to?\n";
    curr_to="GBP";
    //cin>> curr_to;
    //conversion_intermed(umap,curr_from,"USD",curr_to,amount);

    double conversion=corr_mon(umap,curr_from,curr_to,amount);
    
    cout<<conversion;

    //auto point_val= umap.find(curr_from+curr_to);

    last_ask=umap[curr_from][curr_to] -> getAsk();
    last_bid=umap[curr_from][curr_to] -> getBid();

    cout<<last_ask;
    cout<<last_bid;

    atomic<bool> is_running(true);
    thread t1(randomWalk, std::ref(is_running));
    thread t2(std::ref(updater), std::ref(is_running));

    umap["GBP"]["JPY"] -> setAsk(last_ask);
    umap["GBP"]["JPY"] -> setBid(last_bid);

    this_thread::sleep_for(std::chrono::seconds(2));
    is_running=false;

    t1.join();
    t2.join();

    return 0;
};