#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <cmath>
#include <cassert>
#include "random_walk.hpp"
#include "board_updater.hpp"
#include "globals.hpp"

using namespace std;

double rand_between(double a, double b)
{
    assert(a < b);
    return a + (b - a) * double(rand()) / RAND_MAX;
}

int rand_between(int a, int b)
{
    assert(a < b);
    return int(a + (b - a) * double(rand()) / RAND_MAX);
}

void quote_change(atomic<bool> &keep_running, const string pair, float last, float volatility)
{
    unique_lock<mutex> ul_cout(g_mutex_cout, defer_lock);

    ul_cout.lock();
    cout << "RandomWalk thread (" << pair << "): Starting" << endl;

    srand(time(NULL));

    ul_cout.unlock();

    while (keep_running)
    {
        last = last * exp(volatility / sqrt(24.0 * 60.0 * 60.0) * rand_between(-1.0, 1.0) * 4);

        g_quote_updates.push(QuoteUpdate(pair, last));

        this_thread::sleep_for(chrono::milliseconds(rand_between(1000, 5000)));
    }

    ul_cout.lock();
    cout << "RandomWalk thread (" << pair << "): Stopping" << endl;
    ul_cout.unlock();
}
