#include <atomic>
#include <thread>
#include <mutex>
#include <iostream>
#include <cmath>
#include <chrono>
#include <cassert>

#include "randomPriceGen.hpp"

using namespace std;

mutex g_mutex_cout;

//Random value between two values
double rand_between(double a, double b)
{
    assert(a<b);
    return a + (b-a) * double(rand()) / RAND_MAX;
}

int rand_between(int a, int b)
{
    assert(a<b);
    return a + (b-a) * double(rand()) / RAND_MAX;
}

//Function for calculating the random generation of the exchange rate price
void updateRate(atomic<bool> &keep_running, threadSafeQueue<double> &priceQueue, double lastPrice)
{
    g_mutex_cout.lock();
    cout << "Rate Change Thread: Starting" << endl;
    g_mutex_cout.unlock();

    srand(time(NULL));

    while(keep_running)
    {
        //Set new price based on old price * random value
        lastPrice = lastPrice * exp(0.10 /sqrt(24.0 * 60.0 * 60.0) * rand_between(-1.0, 1.0) *4);
        //Push value to queue
        priceQueue.push(lastPrice);
        cout << lastPrice << endl;
        this_thread::sleep_for(chrono::milliseconds(rand_between(2000,5000)));
    }

    g_mutex_cout.lock();
    cout << "Rate Change Thread: Ending" << endl;
    g_mutex_cout.unlock();
}