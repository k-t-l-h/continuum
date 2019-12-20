#ifndef CONTINUUM_MANAGER_H
#define CONTINUUM_MANAGER_H

#include <memory>
#include <thread>
#include <vector>
#include "../Container/Container.h"
#include "../TestCase/TestCaseClass.h"
#include "../Queue/Queue.h"

#include "../TestCase/TestCaseClass.h"

class Manager : public std::enable_shared_from_this<Manager> {

public:

    Manager(std::shared_ptr<Queue<TestCase *>>, std::shared_ptr<Queue<std::string>>, int);

    Manager(const Manager&) = delete;

    Manager& operator=(const Manager&) = delete;

    ~Manager();

    //const std::vector<Container *>& getContainers() const;

    void setWorkingState(bool);

    void run();

private:

    static void worker(std::shared_ptr<Manager> self);

private:

    std::shared_ptr<Queue<TestCase *>> queueIn;

    std::shared_ptr<Queue<std::string>> queueOut;

    std::vector<std::thread> threads;

    std::mutex mutexM;

    bool workStatus = true;

};


#endif //CONTINUUM_WORKER_H
