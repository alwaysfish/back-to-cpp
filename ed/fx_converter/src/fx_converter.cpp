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

int main(int argc, char *argv[])
{
    if (argc == 0 || argc < 3 || string(argv[1]) != "-d")
    {
        cout << "Usage: -d <csv_file_name>" << endl;
        return 1;
    }

    ExchangeBoard board;
    unique_lock<mutex> ul_cout(g_mutex_cout, defer_lock);
    vector<Conversion> conversions;

    conversions.push_back(Conversion("JPY", "EUR", 100000));
    conversions.push_back(Conversion("GBP", "EUR", 100));
    conversions.push_back(Conversion("CAD", "CAD", 200));
    
    if (!board.load_rates(argv[2]))
    {
        cout << "exchange_rates.csv file was not loaded. Exiting..." << endl;
        exit(0);
    }

    atomic<bool> run_threads(true);
    vector<thread> my_threads;

    my_threads.push_back(thread(quote_change, std::ref(run_threads), "EUR/JPY", board.get_rate("EUR/JPY")->get_last(), 0.1));
    my_threads.push_back(thread(quote_change, std::ref(run_threads), "EUR/USD", board.get_rate("EUR/USD")->get_last(), 0.05));
    my_threads.push_back(thread(quote_change, std::ref(run_threads), "GBP/CAD", board.get_rate("GBP/USD")->get_last(), 0.15));
    my_threads.push_back(thread(update_board, std::ref(run_threads), std::ref(board)));

    run_threads = false;

    for (auto & th : my_threads)
        th.join();

    for (auto &c : conversions)
    {
        if (board.convert(c))
        {
            cout << c.amount << " " << c.from << " -> " << c.converted_amount << " " << c.to <<
                " @ " << c.rate << " " << c.pair << endl;
        }
        else
        {
            cout << c.from << " -> " << c.to << " cannot be converted" << endl;
        }
    }

    return 1;
}
