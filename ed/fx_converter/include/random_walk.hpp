#ifndef RANDOM_WALK_HPP
#define RANDOM_WALK_HPP

#include <atomic>
#include "globals.hpp"

void quote_change(std::atomic<bool> &keep_running, const std::string pair, float last, float volatility);

#endif
