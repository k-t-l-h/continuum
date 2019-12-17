#include "Manager.h"
#include <functional>
#include <algorithm>



Manager::Manager(std::shared_ptr<Queue<TestCase *>> qIn, std::shared_ptr<Queue<std::string>> qOut, int count)
        : queueIn(qIn), queueOut(qOut), threads(std::vector<std::thread>(count))
{}

Manager::~Manager() {
    std::for_each(threads.begin(), threads.end(),
            [](std::thread& thread) { if (thread.joinable()) thread.join(); });
}

void Manager::setWorkingState(bool status) {
    workStatus = status;
}

void Manager::worker(std::shared_ptr<Manager> self) {
    while (self->workStatus) {
        self->mutex.lock();
        if (!self->queueIn->empty()) {
            auto test = self->queueIn->pop();
            self->mutex.unlock();
            Container(self->queueOut).doTest(test);
        } else
            self->mutex.unlock();
    }
}

void Manager::run() {
    for (auto it = threads.begin(); it != threads.end(); ++it)
        *it = std::thread(std::bind(worker, shared_from_this()));
}

