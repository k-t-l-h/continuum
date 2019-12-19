#ifndef CONTINUUM_MANAGER_H
#define CONTINUUM_MANAGER_H

#include <memory>
#include <thread>
#include <vector>
#include "../Container/Container.h"
#include "../TestCase/TestCaseClass.h"
#include "../Queue/Queue.h"

#include "../TestCase/TestCaseClass.h"

class Manager {

public:

    Manager(std::shared_ptr<Queue<TestCase *>> queueIn, std::shared_ptr<Queue<std::string>> queueOut, int count);

    Manager(const Manager&) = delete;

    Manager& operator=(const Manager&) = delete;

    ~Manager() = default;

    //const std::vector<Container *>& getContainers() const;

    void workCycle();

    void setWorkingState(bool);

private:

    std::shared_ptr<Queue<TestCase *>> queueIn;

    std::shared_ptr<Queue<std::string>> queueOut;

    std::vector<std::thread> threads;

    std::vector<std::shared_ptr<Container>> containers;

    bool workStatus = true;

};


#endif //CONTINUUM_WORKER_H
