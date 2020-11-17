#include <atomic>
#include <mutex>
#include <ctime> 
#include <random>
#include <chrono>

#include <mutex>


#include "RandomWalk.hpp"

//Goal is to create methods that will produce a random price changes for currencies
void randomWalk(std::atomic<bool>& is_running){
    std::mutex mu;
    double t;

    srand (std::time(NULL));

    while(is_running){
 
        double rand_num= (float) rand() / RAND_MAX;
        
        double x=(0.10/sqrt((24*60*60)))*(rand_num-0.5)*4;

        double price_change=exp(x-1);

        mu.lock();
        last_ask=last_ask+price_change;
        last_bid=last_bid+price_change;
        mu.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(2));


    }

}
