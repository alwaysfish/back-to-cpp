#include <iostream>
using namespace std;

#include "../include/ExchangeBoard.hpp"
#include "../include/ExchangeRate.hpp"
#include "../include/RandomWalk.hpp"
#include "../include/Updater.hpp"

//

int main(){
    nested_unord_map umap;

//- loads exchange rates from a CSV file into nested unordered map

    insertCSV(umap);


//- asks for amount and currency to exchange from, currency to exchange from and the amount exchanged
    cout<<"How much money out?\n";
    //cin>> mon;
    const double amount=50.5;
    
    cout<<"Which currency to exchange from?\n";
    //cin>> curr_from;
    const string  curr_from="USD";

    
    cout<<"Which currency to exchange to?\n";
    const string  curr_to="GBP";
    //cin>> curr_to;

    //Finds intermediate currencies
    //check_intermed(umap,curr_from,"USD",curr_to,amount);


    //Finds conversions and outputs the greatest exchange converter
   double conversion=converter(umap,curr_from,curr_to,amount);
    
    cout<<conversion;

    //auto point_val= umap.find(curr_from+curr_to);
    RandomWalk randW;

    randW.last_ask=umap[curr_from][curr_to]->getAsk();
    randW.last_bid=umap[curr_from][curr_to]->getBid();

    cout<<randW.last_ask;
    cout<<randW.last_bid;

    atomic<bool> is_running(true);
    thread t1(randomWalk, std::ref(is_running),randW);
    thread t2(std::ref(updater), std::ref(is_running),randW);

    umap["GBP"]["JPY"]->setAsk(randW.last_ask);
    umap["GBP"]["JPY"]->setBid(randW.last_bid);

    this_thread::sleep_for(std::chrono::seconds(2));
    is_running=false;

    t1.join();
    t2.join();

    return 0;
};