/*RandomWalk file manages the thread responsible for generating an updated
value for the currency exchange rate */

#include <atomic>

using namespace std;

void change_rate(atomic<bool> &keep_running);