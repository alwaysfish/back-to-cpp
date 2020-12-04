/*RandomWalk file manages the thread responsible for generating an updated
value for the currency exchange rate */

#include <atomic>
#include "priceUpdateQueue.hpp"

using namespace std;

void updateRate(atomic<bool> &keep_running, threadSafeQueue<double> &priceQueue, double lastPrice);