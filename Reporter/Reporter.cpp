#include "Reporter.h"
#include "../Queue/Queue.h"

Reporter::Reporter(::Queue<JsonObject> *queue, DataBase *db) : Queue(Queue), DB(DB)
{}

void Reporter::WorkCycle() {
    while (true) {
        if (!Queue->empty()) {
            JsonObject obj = Queue->pop();
            PutInDB(obj);
            std::thread t(std::bind(&Reporter::Notify, this));
            t.detach();
        }
    }
}