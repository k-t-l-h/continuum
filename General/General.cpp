#include <General.h>

General::General() {
    rqueue = std::make_shared<Queue<std::string>>();
    pqueue = std::make_shared<Queue<std::string>>();
    wqueue = std::make_shared<Queue<TestCase*>>();
    db = std::make_shared<Queue<DataBase>>();
    parsers.push_back(Parser(pqueue, wqueue, rqueue));
    managers.push_back(Manager(wqueue, rqueue, 1));
    reporters.push_back(Reporter(rqueue, db));
}

General::General(int cont_count) {
    rqueue = std::make_shared<Queue<std::string>>();
    pqueue = std::make_shared<Queue<std::string>>();
    wqueue = std::make_shared<Queue<TestCase*>>();
    db = std::make_shared<Queue<DataBase>>();
    parsers.push_back(Parser(pqueue, wqueue, rqueue));
    managers.push_back(Manager(wqueue, rqueue, cont_count));
    reporters.push_back(Reporter(rqueue, db));
}

General::General(int p_count, int m_count, int r_count, int cont_count) {
    rqueue = std::make_shared<Queue<std::string>>();
    pqueue = std::make_shared<Queue<std::string>>();
    wqueue = std::make_shared<Queue<TestCase*>>();
    db = std::make_shared<Queue<DataBase>>();
    for (int i = 0; i < p_count; ++i)
        parsers.push_back(Parser(pqueue, wqueue, rqueue));
    for (int i = 0; i < m_count; ++i)
        managers.push_back(Manager(wqueue, rqueue, cont_count));
    for (int i = 0; i < r_count; ++i)
        reporters.push_back(Reporter(rqueue, db));
}

void General::TurnOn() {
    for (auto ptr = parser.begin(); ptr < parsers.end(); ptr++)
    {
        boost::thread thr(*ptr->WorkCycle());
        thr.detach();
    }
    for (auto ptr = managers.begin(); ptr < managers.end(); ptr++)
    {
        boost::thread thr(*ptr->WorkCycle());
        thr.detach();
    }
    for (auto ptr = reporters.begin(); ptr < reporters.end(); ptr++)
    {
        boost::thread thr(*ptr->WorkCycle());
        thr.detach();
    }
}