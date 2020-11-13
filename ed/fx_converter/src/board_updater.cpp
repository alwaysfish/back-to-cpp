#include <thread>
#include <chrono>
#include <iostream>
#include "board_updater.hpp"
#include "globals.hpp"

using namespace std;


void update_board(std::atomic<bool> &keep_running, ExchangeBoard &board)
{
    unique_lock<mutex> ul_cout(g_mutex_cout, defer_lock);

    ul_cout.lock();
    cout << "BoardUpdater thread: Starting" << endl;
    ul_cout.unlock();

    while (keep_running)
    {
        while (!g_quote_updates.empty())
        {
            const QuoteUpdate &qu = g_quote_updates.front();

            board.update_rate(qu.pair, qu.last);

            ul_cout.lock();
            cout << "BoardUpdater thread: Last quote for " << qu.pair << " " 
                << board.get_rate(qu.pair)->get_last() << endl;
            ul_cout.unlock();

            g_quote_updates.pop();
        }

        this_thread::sleep_for(chrono::milliseconds(200));
    }

    ul_cout.lock();
    cout << "BoardUpdater thread: Stopping" << endl;
    ul_cout.unlock();
}
