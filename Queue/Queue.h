//
// Created by Keenshi on 26.10.2019.
//

#ifndef CONTINUUM_QUEUE_H
#define CONTINUUM_QUEUE_H

#include <mutex>
#include <queue>
#include <string>

typedef std::string JsonObject 


template<class T>
class Queue {
public:
    Queue() : std::queue<T>(), std::mutex() {}
    void push(T);
    T pop();
    bool empty();
private:
    std::queue<T> queue;
    std::mutex qmutex;
};




#endif //CONTINUUM_QUEUE_H
