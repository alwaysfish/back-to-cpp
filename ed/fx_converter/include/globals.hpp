#pragma once

#include <mutex>
#include <atomic>
#include <queue>
#include "shared_queue.hpp"

struct QuoteUpdate
{
    std::string pair;
    double last;

    QuoteUpdate(const std::string &p, double l) : pair{p}, last{l} {}
};

extern std::mutex g_mutex_cout;

extern SharedQueue<QuoteUpdate> g_quote_updates;
