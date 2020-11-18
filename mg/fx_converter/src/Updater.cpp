#include <chrono>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

#include "Updater.hpp"

//Update the ExchangeRates with the price changes in Random Walk.cpp
void updater(atomic<bool>& is_running){
    condition_variable wait_blocks;
    mutex mtx;

    //loop while the random walk is_running and add the calculated values to ExchangeRates
    while(is_running){
        
        unique_lock<std::mutex> lck (mtx);
        
        wait_blocks.wait_for(lck, chrono::seconds(2));
        
        
    }
}
