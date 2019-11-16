//
// Created by evgeny on 26.10.2019.
//

#ifndef CONTINUUM_REPORTER_H
#define CONTINUUM_REPORTER_H

#include <string>
#include "../Queue/Queue.h"
#include "../DataBase/DataBase.h"
#include "../JsonObject/JsonObject.h"

class Reporter {

public:

    explicit Reporter(Queue<JsonObject> &queue, DataBase &db);

    Reporter(const Reporter&) = delete;

    Reporter& operator=(const Reporter&) = delete;

    ~Reporter() = default;

    void WorkCycle();

    bool PutInDB(const JsonObject& elem);

    bool Notify();

private:

    Queue<JsonObject> &queue;

    DataBase &db;

};


#endif //CONTINUUM_REPORTER_H
