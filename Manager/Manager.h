#ifndef CONTINUUM_MANAGER_H
#define CONTINUUM_MANAGER_H

#include <memory>
#include <vector>
#include "../Container/Container.h"
#include "../TestCase/TestCaseClass.h"
#include "../Queue/Queue.h"

#include "../TestCase/TestCaseClass.h"

class Manager {

public:

    Manager(std::shared_ptr<Queue<TestCase *>> QueueIn, std::shared_ptr<std::string> QueueOut, int count);

    Manager(const Manager&) = delete;

    Manager& operator=(const Manager&) = delete;

    ~Manager() = default;

    const std::vector<Container *>& GetContainers() const;

    int getCountContainers() const;

    void workCycle();

    void setWorkingState(bool WorkSatus);

private:

    std::shared_ptr<Queue<TestCase *>> QueueIn;

    std::shared_ptr<std::string> QueueOut;

    std::vector<Container> containers;

    bool workSatus = true;

};


#endif //CONTINUUM_WORKER_H
