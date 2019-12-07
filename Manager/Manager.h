#ifndef CONTINUUM_MANAGER_H
#define CONTINUUM_MANAGER_H

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

    int getCountContainers() const;

    void workCycle();

    void setWorkingState(bool WorkSatus);

private:

    Queue<TestCase *> *QueueIn;

    Queue<JsonObject> *QueueOut;

    std::vector<Container> containers;

    bool workSatus = true;

};


#endif //CONTINUUM_WORKER_H
