#ifndef CONTINUUM_WORKER_H
#define CONTINUUM_WORKER_H

#include <vector>
#include "../Container/Container.h"
#include "../Queue/Queue.h"
#include "../TestCase/TestCaseClass.h"

class Manager {

public:

    explicit Manager(Queue<TestCase *> &queue, int count);

    Manager(const Manager&) = delete;

    Manager& operator=(const Manager&) = delete;

    ~Manager() = default;

    int GetCountContainers() const;

    Queue<TestCase *> GetQueue() const;

    Queue<TestCase *>& GetQueue();

    std::vector<Container>  GetContainers() const;

    std::vector<Container>&  GetContainers();

    void WorkCycle() const;


private:

    Queue<TestCase *> queue;

    std::vector<Container> array;

};


#endif //CONTINUUM_WORKER_H
