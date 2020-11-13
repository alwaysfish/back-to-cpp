#pragma once

#include <queue>
#include <mutex>

template <typename T>
class SharedQueue
{
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;

public:
    const T& front();
    void pop();

    void push(const T& item);

    int size();
    bool empty();
};


template <typename T>
const T& SharedQueue<T>::front()
{
    std::lock_guard<std::mutex> ul(m_mutex);
    return m_queue.front();
}

template <typename T>
void SharedQueue<T>::pop()
{
    std::lock_guard<std::mutex> ul(m_mutex);
    m_queue.pop();
}

template <typename T>
void SharedQueue<T>::push(const T& item)
{
    std::lock_guard<std::mutex> ul(m_mutex);
    m_queue.push(item);
}

template <typename T>
int SharedQueue<T>::size()
{
    std::lock_guard<std::mutex> ul(m_mutex);
    return m_queue.size();
}

template <typename T>
bool SharedQueue<T>::empty()
{
    std::lock_guard<std::mutex> ul(m_mutex);
    return m_queue.empty();
}