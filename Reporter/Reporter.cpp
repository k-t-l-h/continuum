#include "Reporter.h"
#include "../Queue/Queue.h"
#include <functional>

Reporter::Reporter(std::shared_ptr<Queue<std::string>> queue, std::shared_ptr<Database> db, int count)
    : queue(queue), db(db), threads(std::vector<std::pair<std::thread, bool>>(count))
{}

void Reporter::setWorkingState(bool status) {
    workStatus = status;
}

void Reporter::notify(bool& status) {
    status = true;
}

void Reporter::workCycle() {
    while (workStatus) {
        if (!queue->empty()) {
            std::string obj = queue->pop();
            if (db->insert(obj))
                for (int i = 0; i < threads.size(); ++i)
                    if (!threads[i].first.joinable()) {
                        threads[i].second = false;
                        threads[i].first = std::thread(std::bind(&Reporter::notify, std::ref(*this), std::ref(threads[i].second)));
                        break;
                    }
        }
        for (int i = 0; i < threads.size(); ++i)
            if (threads[i].second && threads[i].first.joinable())
                threads[i].first.join();
    }
    for (int i = 0; i < threads.size(); ++i)
        if (threads[i].first.joinable())
            threads[i].first.join();
}
