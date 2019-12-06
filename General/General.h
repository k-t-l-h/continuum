#ifndef CONTINUUM_GENERAl_H
#define CONTINUUM_GENERAL_H

#include "../Queue/Queue.h"
#include "../Parser/Parser.h"
#include "../Manager/Manager.h"
#include "../Reporter/Reporter.h"
#include "../TestCase/TestCase.h"
#include "../DataBase/DataBase.h"

#include <algorithm>
#include <functional>
#include <thread>
#include <vector>
#include <memory>
#include <string>

class General {
public:
    General(int cont_count = 3, int p_count = 1, int m_count = 1, int r_count = 1);
    ~General();

    void TurnOn();
    void TurnOff();
    int GetRequest(std::string request);
private:
    std::shared_ptr<Queue<std::string>> rqueue;
    std::shared_ptr<Queue<std::string>> pqueue;
    std::shared_ptr<Queue<TestCase*>> wqueue;
    std::shared_ptr<DataBase> db;
    std::vector<Parser> parsers;
    std::vector<Manager> managers;
    std::vector<Reporter> reporters;
    std::vector<std::thread> threads;
}

#endif //CONTINUUM_GENERAL_H