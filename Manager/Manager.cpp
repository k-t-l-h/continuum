#include "Manager.h"
#include <functional>


Manager::Manager(std::shared_ptr<Queue<TestCase *>> queueIn, std::shared_ptr<Queue<std::string>> queueOut, int count)
        : queueIn(queueIn), queueOut(queueOut), threads(count), containers(count)
{
    for (int i = 0; i < containers.size(); ++i)
        containers[i] = std::make_shared<Container>(queueOut);
}



void Manager::setWorkingState(bool status) {
    workStatus = status;
}

#include <iostream>

void Manager::workCycle() {
    while (workStatus) {
        if (!queueIn->empty()) {
            std::cout << "Manager: Send test" << std::endl;
            TestCase *test = queueIn->pop();
            for (int i = 0; i < threads.size(); ++i)
                if (!threads[i].joinable()) {
                    threads[i] = std::thread(std::bind(&Container::doTest, std::ref(containers[i]), std::ref(test)));
                    break;
                }
        }
        for (int i = 0; i < containers.size(); ++i)
            if (containers[i]->isFree() && threads[i].joinable()) {
                std::cout << "Manager: join thread" << std::endl;
                threads[i].join();
            }
    }
    for (int i = 0; i < containers.size(); ++i)
        if (threads[i].joinable())
            threads[i].join();
}