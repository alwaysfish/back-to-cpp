#include <atomic>
#include <thread>
#include <mutex>
#include <iostream>
#include <cmath>
#include <chrono>
#include <cassert>

#include "randomWalk.hpp"

using namespace std;

mutex g_mutex_cout;
atomic<double> quoteRand;

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


void change_rate(atomic<bool> &keep_running)
{
    g_mutex_cout.lock();
    cout << "Rate Change Thread: Starting" << endl;
    g_mutex_cout.unlock();

    srand(time(NULL));

    while(keep_running)
    {
        quoteRand = quoteRand * exp(0.10 /sqrt(24.0 * 60.0 * 60.0) * rand_between(-1.0, 1.0) *4);
        cout << quoteRand << endl;
        this_thread::sleep_for(chrono::milliseconds(rand_between(2000,5000)));
    }

    g_mutex_cout.lock();
    cout << "Rate Change Thread: Ending" << endl;
    g_mutex_cout.unlock();
}