//
// Created by Keenshi on 26.10.2019.
//

#ifndef CONTINUUM_QUEUE_H
#define CONTINUUM_QUEUE_H

#include <mutex>
#include <queue>


template<class T>
class Queue: std::queue {
public:
    void push(T);
    T pop();
private:
    std::mutex qmutex;
};




#endif //CONTINUUM_QUEUE_H
