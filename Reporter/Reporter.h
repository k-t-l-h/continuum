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

class Reporter : public std::enable_shared_from_this<Reporter>{

public:

    Reporter(std::shared_ptr<Queue<std::string>>, std::shared_ptr<Queue<std::string>>, std::shared_ptr<Database>, int);

    Reporter(const Reporter&) = delete;

    Reporter& operator=(const Reporter&) = delete;

    ~Reporter();

    void run();

    void setWorkingState(bool);

private:

    static void worker(std::shared_ptr<Reporter> self);

private:

    std::shared_ptr<Queue<std::string>> queueIn;

    std::shared_ptr<Queue<std::string>> queueOut;

    std::shared_ptr<Database> db;

    std::vector<std::thread> threads;

    std::mutex mutexR;

    bool workStatus = true;

};


#endif //CONTINUUM_REPORTER_H
