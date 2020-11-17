#pragma once
#include <atomic>
#include <unordered_map>
#include <string>
#include <thread>

double last_ask;
double last_bid;

void randomWalk(std::atomic<bool>& is_running);