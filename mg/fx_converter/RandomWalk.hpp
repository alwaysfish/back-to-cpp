#pragma once
#include <atomic>

#include "ExchangeRate.hpp"

double last_ask;
double last_bid;

void randomWalk(std::atomic<bool>& is_running);