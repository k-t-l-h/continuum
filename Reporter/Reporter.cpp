#include "Reporter.h"
#include "../Queue/Queue.h"

Reporter::Reporter(std::shared_ptr<Queue<std::string>> queue, std::shared_ptr<DataBase> db) : queue(queue), db(db)
{}

void Reporter::setWorkingState(bool status) {
    workSatus = status;
}

void Reporter::WorkCycle() {
    while (workStatus) {
        if (!Queue->empty()) {
            std::string obj = Queue->pop();
            putInDB(obj);
            std::thread t(std::bind(&Reporter::Notify, this));
            t.detach();
        }
    }
}

bool putInDB(const JsonObject& elem) {
    db->insert(elem);
    return true;
}