#include "Reporter.h"
#include "../Queue/Queue.h"

Reporter::Reporter(std::shared_ptr<Queue<std::string>> queue, std::shared_ptr<Database> db) : queue(queue), db(db)
{}

void Reporter::setWorkingState(bool status) {
    workStatus = status;
}

void Reporter::workCycle() {
    while (workStatus) {
        if (!queue->empty()) {
            std::string obj = Queue->pop();
            putInDB(obj);
            std::thread t(std::bind(&Reporter::notify, this));
            t.detach();
        }
    }
}

bool putInDB(const std::string& elem) {
    db->insert(elem);
    return true;
}