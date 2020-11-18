#include <atomic>
#include <mutex>
#include <ctime> 
#include <condition_variable>
#include <random>
#include <chrono>

#include <mutex>


#include "../include/RandomWalk.hpp"

//Goal is to create methods that will produce a random price changes for currencies
void randomWalk(std::atomic<bool>& is_running,RandomWalk randW){
    std::condition_variable wait_blocks;
    std::mutex mu;
    double t;

    srand (std::time(NULL));

    while(is_running){
 
        double rand_num= (float) rand() / RAND_MAX;
        
        double x=(0.10/sqrt((24*60*60)))*(rand_num-0.5)*4;

        double price_change=exp(x-1);

        std::unique_lock<std::mutex> lck (mu);
        randW.last_ask=randW.last_ask+price_change;
        randW.last_bid=randW.last_bid+price_change;

        std::this_thread::sleep_for(std::chrono::seconds(2));



    }

}
