//
// Created by evgeny on 26.10.2019.
//

#ifndef CONTINUUM_REPORTER_H
#define CONTINUUM_REPORTER_H

#include "../Queue/Queue.h"
#include "../Database/Database.h"
#include "../TestCase/TestCaseClass.h"
#include <string>
#include <thread>
#include <functional>
#include <memory>

class Reporter {

public:

    Reporter(std::shared_ptr<Queue<std::string>> queue, std::shared_ptr<Database> db, int count);

    Reporter(const Reporter&) = delete;

    Reporter& operator=(const Reporter&) = delete;

    ~Reporter() = default;

    void workCycle();

    void setWorkingState(bool);

    void notify(bool &);

private:

    std::shared_ptr<Queue<std::string>> queue;

    std::shared_ptr<Database> db;

    std::vector<std::pair<std::thread, bool>> threads;

    bool workStatus = true;

};


#endif //CONTINUUM_REPORTER_H
