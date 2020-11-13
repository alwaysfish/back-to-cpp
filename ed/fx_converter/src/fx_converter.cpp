#include <memory>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>
#include "exchange_board.hpp"
#include "exchange_rate.hpp"
#include "random_walk.hpp"
#include "board_updater.hpp"
#include "globals.hpp"

using namespace std;

int main()
{
    ExchangeBoard board;
    unique_lock<mutex> ul_cout(g_mutex_cout, defer_lock);
    
    if (!board.load_rates("./../../../datasets/exchange_rates.csv"))
    {
        cout << "exchange_rates.csv file was not loaded. Exiting..." << endl;
        exit(0);
    }

    atomic<bool> run_threads(true);
    thread th_gen1(quote_change, std::ref(run_threads), "EUR/JPY", board.get_rate("EUR/JPY")->get_last(), 0.1);
    thread th_gen2(quote_change, std::ref(run_threads), "EUR/USD", board.get_rate("EUR/USD")->get_last(), 0.05);
    thread th_gen3(quote_change, std::ref(run_threads), "GBP/CAD", board.get_rate("GBP/USD")->get_last(), 0.15);
    thread th_update(update_board, std::ref(run_threads), std::ref(board));

    this_thread::sleep_for(chrono::seconds(15));

    run_threads = false;

    board.convert("JPY", "EUR", 100000);
    board.convert("GBP", "EUR", 100);
    board.convert("CAD", "CAD", 200);

    th_gen1.join();
    th_gen2.join();
    th_gen3.join();
    th_update.join();
}
