//
// Created by evgeny on 26.10.2019.
//

#ifndef CONTINUUM_REPORTER_H
#define CONTINUUM_REPORTER_H

#include <memory>
#include "../Queue/Queue.h"
#include "../DataBase/DataBase.h"
#include "../JsonObject/JsonObject.h"
#include "../TestCase/TestCaseClass.h"
#include <string>
#include <thread>
#include <functional>

class Reporter {

public:

    Reporter(std::shared_ptr<Queue<std::string>> queue, std::shared_ptr<Database> db);

    Reporter(const Reporter&) = delete;

    Reporter& operator=(const Reporter&) = delete;

    ~Reporter() = default;

    void workCycle();

    void setWorkingState(bool WorkSatus);

    bool putInDB(const std::string& elem);

    bool notify();

private:

    std::shared_ptr<Queue<std::string>> queue;

    std::shared_ptr<Database> db;

    bool workStatus = true;

};


#endif //CONTINUUM_REPORTER_H
