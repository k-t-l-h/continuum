#include "Reporter.h"
#include "../Queue/Queue.h"
#include <functional>

Reporter::Reporter(std::shared_ptr<Queue<std::string>> qIn, std::shared_ptr<Queue<std::string>> qOut, std::shared_ptr<Database> db, int count)
    : queueIn(qIn), queueOut(qOut), db(db), threads(std::vector<std::thread>(count))
{}

Reporter::~Reporter(){
    std::for_each(threads.begin(), threads.end(),
                  [](std::thread& thread) { if (thread.joinable()) thread.join(); });
}

void Reporter::setWorkingState(bool status) {
    workStatus = status;
}

void Reporter::worker(std::shared_ptr<Reporter> self) {
    while (self->workStatus) {
        self->mutex.lock();
        if (!self->queueIn->empty()) {
            std::string answer = self->queueIn->pop();
            self->mutex.unlock();
            self->db->insert(answer);
            self->queueOut->push(answer);
        } else
            self->mutex.unlock();
    }
}

void Reporter::run() {
    for (auto it = threads.begin(); it != threads.end(); ++it)
        *it = std::thread(std::bind(worker, shared_from_this()));
}



