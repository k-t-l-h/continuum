#ifndef CONTINUUM_WORKER_H
#define CONTINUUM_WORKER_H

#include <vector>
#include "../Container/Container.h"
#include "../Queue/Queue.h"
#include "../TestCase/TestCaseClass.h"

class Manager {

public:

    explicit Manager(Queue<TestCase *> &QueueIn, Queue<std::string> &QueueOut, int count);

    Manager(const Manager&) = delete;

    Manager& operator=(const Manager&) = delete;

    ~Manager() = default;

    std::vector<Container *>& GetContainers();

    int GetCountContainers();


    void WorkCycle();

private:

    Queue<TestCase *> QueueIn;

    Queue<std::string> QueueOut;

    std::vector<Container *> Containers;

};


#endif //CONTINUUM_WORKER_H
