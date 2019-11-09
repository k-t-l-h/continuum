//
// Created by evgeny on 26.10.2019.
//

#ifndef CONTINUUM_REPORTER_H
#define CONTINUUM_REPORTER_H

#include <string>
#include "../Queue/Queue.h"
#include "../DataBase/DataBase.h"

template <class T>
class Reporter {

public:

    explicit Reporter(Queue<T> &queue, DataBase &db);

    Reporter(const Reporter&) = delete;

    Reporter& operator=(const Reporter&) = delete;

    ~Reporter() = default;

    Queue<T> GetQueue() const;

    Queue<T>& GetQueue();

    DataBase GetDB() const;

    DataBase& GetDB();

    virtual void WorkCycle();

    void PutInDB(const T& elem);

    void Notify();

private:

    Queue<T> &queue;

    DataBase &db;

};


#endif //CONTINUUM_REPORTER_H
