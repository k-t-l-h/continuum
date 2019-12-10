#include "Manager.h"
#include <thread>
#include <functional>

Manager::Manager(std::shared_ptr<Queue<TestCase *>> QueueIn, std::shared_ptr<Queue<std::string>> QueueOut, int count)
: QueueIn(QueueIn), QueueOut(QueueOut), Containers(std::vector<Container>(count, QueueOut))
{}

int Manager::GetCountContainers() const {
    return Containers.size();
}

void Manager::setWorkingState(bool status) {
    workSatus = status;
}

void Manager::workCycle() {
    while (workSatus) {
        if (!QueueIn->empty()) {
            TestCase* test = QueueIn->pop();
            for (auto& container : Containers)
                if (container.isFree()) {
                    std::thread t(std::bind(&Container::doTest, container, *test));
                    t.detach();
                    break;
                }
        }
    }
}