//
// Created by evgeny on 26.10.2019.
//

#ifndef CONTINUUM_REPORTER_H
#define CONTINUUM_REPORTER_H

#include "../Queue/Queue.h"
#include "../DataBase/DataBase.h"
#include "../JsonObject/JsonObject.h"
#include "../TestCase/TestCaseClass.h"
#include <thread>
#include <functional>

class Reporter {

public:

    Reporter(Queue<JsonObject> *queue, DataBase *db);

    Reporter(const Reporter&) = delete;

    Reporter& operator=(const Reporter&) = delete;

    ~Reporter() = default;

    void WorkCycle();

    bool PutInDB(const JsonObject& elem);

    bool Notify();

private:

    Queue<JsonObject> *Queue;

    DataBase *DB;

};


#endif //CONTINUUM_REPORTER_H
