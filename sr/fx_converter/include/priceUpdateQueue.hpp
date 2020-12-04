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

public:
        threadSafeQueue() = default;
        threadSafeQueue(const threadSafeQueue<T> &) = delete;
        threadSafeQueue& operator=(const threadSafeQueue<T> &) = delete;
        threadSafeQueue(threadSafeQueue<T>&& other) {
            lock_guard<mutex> lock(mut);
            priceQueue = move(other.priceQueue);
        }

        void push(const T &value)
        {
            lock_guard<mutex> lock(mut);
            priceQueue.push(value);
        }
        void waitAndPop(T& value)
        {
            unique_lock<mutex> lock(mut);
            T tmp = priceQueue.front();
            priceQueue.pop();
            return tmp;
        }
        
};