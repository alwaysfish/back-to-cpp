#pragma once
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "RandomWalk.hpp"

void updater(bool& is_running);