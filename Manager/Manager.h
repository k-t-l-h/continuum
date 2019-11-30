#ifndef CONTINUUM_WORKER_H
#define CONTINUUM_WORKER_H

#include <vector>
#include "../Container/Container.h"
#include "../Queue/Queue.h"
#include "../TestCase/TestCaseClass.h"

class Manager {

public:

    Manager(Queue<TestCase *> *QueueIn, Queue<JsonObject> *QueueOut, int count);

    Manager(const Manager&) = delete;

    Manager& operator=(const Manager&) = delete;

    ~Manager() = default;

    const std::vector<Container *>& GetContainers() const;

    int GetCountContainers() const;


    void WorkCycle();

private:

    Queue<TestCase *> *QueueIn;

    Queue<JsonObject> *QueueOut;

    std::vector<Container> Containers;

};


#endif //CONTINUUM_WORKER_H
