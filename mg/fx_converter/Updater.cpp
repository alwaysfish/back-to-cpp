#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

#include "Updater.hpp"

//Update the ExchangeRates with the price changes in Random Walk.cpp
void updater(bool& is_running){
    condition_variable wait_blocks;
    mutex mtx;
    for (int i=0;i<5;i++){
        
        unique_lock<std::mutex> lck (mtx);
        
        wait_blocks.wait_for(lck, chrono::seconds(2));
        
        
    }
}
