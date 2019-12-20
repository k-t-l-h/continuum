#include "General.h"

std::mutex m;
std::mutex pmutex;
std::condition_variable condition;
bool notified;

General::General(int cont_count, int p_count, int m_count, int r_count) {
    rqueue = std::make_shared<Queue<std::string>>();
    pqueue = std::make_shared<Queue<std::string>>();
    wqueue = std::make_shared<Queue<TestCase*>>();
    db = std::make_shared<Database>();
    for (int i = 0; i < p_count; ++i) {
        parsers.push_back(std::make_shared<Parser>(pqueue, wqueue, rqueue));
    }
    for (int i = 0; i < m_count; ++i)
        managers.push_back(std::make_shared<Manager>(wqueue, rqueue, cont_count));
    for (int i = 0; i < r_count; ++i)
        reporters.push_back(std::make_shared<Reporter>(rqueue, db, 5));
}

void General::turnOn() {
    for (auto ptr = parsers.begin(); ptr < parsers.end(); ptr++)
    {
        (*ptr)->setStatus(true);
        std::thread thr(std::bind(&Parser::workCycle, std::ref(*ptr)));
        threads.emplace_back(std::move(thr));
    }
    for (auto ptr = managers.begin(); ptr < managers.end(); ptr++)
    {
        (*ptr)->setWorkingState(true);
        std::thread thr(std::bind(&Manager::workCycle, std::ref(*ptr)));
        threads.emplace_back(std::move(thr));
    }
    for (auto ptr = reporters.begin(); ptr < reporters.end(); ptr++)
    {
        (*ptr)->setWorkingState(true);
        std::thread thr(std::bind(&Reporter::workCycle, std::ref(*ptr)));
        threads.emplace_back(std::move(thr));
    }
}

void General::turnOff() {
    for (auto ptr = parsers.begin(); ptr < parsers.end(); ptr++)
    {
        (*ptr)->setStatus(false);
    }
    for (auto ptr = managers.begin(); ptr < managers.end(); ptr++)
    {
        (*ptr)->setWorkingState(false);
    }
    for (auto ptr = reporters.begin(); ptr < reporters.end(); ptr++)
    {
        (*ptr)->setWorkingState(false);
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

void General::getRequest(std::string request) {
    std::unique_lock<std::mutex> lock(m);
    rqueue->push(request);
    notified = true;
    condition.notify_one();
}

int main() {
    General server = General();
    server.turnOn();
    sleep(1);
    std::string input = "{\"request\":{\"id\":\"234\",\"request_type\":\"1\",\"host\":\"localhost\",\"protocol\":\"0\",\"method\":\"0\",\"reference\":\"200\"}}";
    server.getRequest(input);
    while (true)
        sleep(1);
    server.turnOff();
    return 0;
}