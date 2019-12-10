#include <General.h>

General::General(int cont_count, int p_count, int m_count, int r_count) {
    rqueue = std::make_shared<Queue<std::string>>();
    pqueue = std::make_shared<Queue<std::string>>();
    wqueue = std::make_shared<Queue<TestCase*>>();
    db = std::make_shared<Queue<Database>>();
    for (int i = 0; i < p_count; ++i)
        parsers.push_back(Parser(pqueue, wqueue, rqueue));
    for (int i = 0; i < m_count; ++i)
        managers.push_back(Manager(wqueue, rqueue, cont_count));
    for (int i = 0; i < r_count; ++i)
        reporters.push_back(Reporter(rqueue, db));
}

void General::turnOn() {
    for (auto ptr = parser.begin(); ptr < parsers.end(); ptr++)
    {
        *ptr->setWorkingState(true);
        std::thread thr(*ptr->workCycle);
        threads.push_back(thr);
    }
    for (auto ptr = managers.begin(); ptr < managers.end(); ptr++)
    {
        *ptr->setWorkingState(true);
        std::thread thr(*ptr->workCycle);
        threads.push_back(thr);
    }
    for (auto ptr = reporters.begin(); ptr < reporters.end(); ptr++)
    {
        *ptr->setWorkingState(true);
        std::thread thr(*ptr->workCycle);
        threads.push_back(thr);
    }
}

void General::turnOff() {
    for (auto ptr = parser.begin(); ptr < parsers.end(); ptr++)
    {
        *ptr->setWorkingState(false);
    }
    for (auto ptr = managers.begin(); ptr < managers.end(); ptr++)
    {
        *ptr->setWorkingState(false);
    }
    for (auto ptr = reporters.begin(); ptr < reporters.end(); ptr++)
    {
        *ptr->setWorkingState(false);
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join()));
}

void General::getRequest(std::string request) {
    std::unique_lock<std::mutex> lock(m);
    *rqueue->push(request);
    notified = true;
    condition.notify_one();
}