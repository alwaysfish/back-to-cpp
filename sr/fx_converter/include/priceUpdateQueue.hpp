#include <condition_variable>
#include <mutex>
#include <iostream>
#include <queue>
#include <memory>

using namespace std;

template <typename T>
class threadSafeQueue
{
    private:
        mutable mutex mut;
        queue<T> priceQueue;
        condition_variable dataCond;

public:
        threadSafeQueue() {};
        threadSafeQueue(const threadSafeQueue& other)
        {
            lock_guard<mutex> lock(mut);
            priceQueue = other.priceQueue;
        }
        threadSafeQueue& operate=(const threadSafeQueue& other) = delete;
        void push(T value)
        {
            lock_guard<mutex> lock(mut);
            priceQueue.push(value);
            dataCond.notify_one();

        }
        void waitAndPop(T& value)
        {
            unique_lock<mutex> lock(mut);
            dataCond.wait(lock, [this]{return !priceQueue.empty();});
            value = priceQueue.front();
            priceQueue.pop();
        }
        
};