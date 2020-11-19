#pragma once
#include <atomic>
#include <unordered_map>
#include <string>
#include <thread>

struct RandomWalk{
    double last_ask=0;
    double last_bid=0;
};



void randomWalk(std::atomic<bool> is_running,RandomWalk randW);