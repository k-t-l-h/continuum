//
// Created by Keenshi on 26.10.2019.
//

#ifndef CONTINUUM_QUEUE_H
#define CONTINUUM_QUEUE_H

#include <mutex>
#include <queue>

template<class T>
class Queue {
public:
    void push(T value);
    T pop();
    bool empty();
private:
    std::queue<T> q;
    std::mutex qmutex;
};

template<class T>
void Queue<T>::push(T value) {
    const std::lock_guard<std::mutex> guard(qmutex);
    q.push(value);
}

template<class T>
T Queue<T>::pop() {
    const std::lock_guard<std::mutex> guard(qmutex);
    T top = q.front();
    q.pop();
    return top;
}

template<class T>
bool Queue<T>::empty() {
    const std::lock_guard<std::mutex> guard(qmutex);
    return q.empty();
}

#endif //CONTINUUM_QUEUE_H
