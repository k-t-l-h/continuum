#ifndef CONTINUUM_GENERAl_H
#define CONTINUUM_GENERAL_H

#include "../Queue/Queue.h"
#include "../Parser/Parser.h"
#include "../Manager/Manager.h"
#include "../Reporter/Reporter.h"
#include "../TestCase/TestCaseClass.h"
#include "../Database/Database.h"

#include <algorithm>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>
#include <memory>
#include <string>


class General {
public:
    General(int cont_count = 3, int p_count = 1, int m_count = 1, int r_count = 1);
    ~General();

    void turnOn();
    void turnOff();
    void getRequest(std::string request);
private:
    std::shared_ptr<Queue<std::string>> rqueue;
    std::shared_ptr<Queue<std::string>> pqueue;
    std::shared_ptr<Queue<TestCase*>> wqueue;
    std::shared_ptr<Database> db;
    std::vector<std::shared_ptr<Parser>> parsers;
    std::vector<std::shared_ptr<Manager>> managers;
    std::vector<std::shared_ptr<Reporter>> reporters;
    std::vector<std::thread> threads;
};

#endif //CONTINUUM_GENERAL_H