#include "Manager.h"
#include <thread>
#include <functional>

Manager::Manager(Queue<TestCase *> *QueueIn, Queue<std::string> *QueueOut, int count)
: QueueIn(QueueIn), QueueOut(QueueOut), Containers(std::vector<Container>(count, QueueOut))
{}

int Manager::GetCountContainers() const {
    return Containers.size();
}

void Manager::WorkCycle() {
    while (true) {
        if (!QueueIn->empty()) {
            TestCase* test = QueueIn->pop();
            for (auto& container : Containers)
                if (container.IsFree()) {
                    std::thread t(std::bind(&Container::DoTest, container, *test));
                    t.detach();
                    break;
                }
        }
    }
}