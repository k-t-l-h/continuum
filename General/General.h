#ifndef CONTINUUM_GENERAL_H
#define CONTINUUM_GENERAL_H

#include "../Queue/Queue.h"
#include "../Parser/Parser.h"
#include "../Manager/Manager.h"
#include "../Reporter/Reporter.h"
#include "../TestCase/TestCaseClass.h"
#include "../Database/Database.h"

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <algorithm>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>
#include <memory>
#include <string>

class Session;

class General {
public:
    General(int);
    void turnOn();
    void turnOff();
    void getRequest(const std::string& request);
    std::pair<bool, std::string> sendAnswer(int id);
    void addSession(boost::shared_ptr<Session>);
    void removeSession(boost::shared_ptr<Session>);
    std::pair<bool, boost::shared_ptr<Session>> findSession(boost::shared_ptr<Session>);
private:
    std::shared_ptr<Queue<std::string>> rqueue;
    std::shared_ptr<Queue<std::string>> pqueue;
    std::shared_ptr<Queue<TestCase*>> wqueue;
    std::shared_ptr<Database> db;
    std::shared_ptr<Parser> parser;
    std::shared_ptr<Manager> manager;
    std::shared_ptr<Reporter> reporter;
    std::vector<std::thread> threads;
    std::vector<boost::shared_ptr<Session>> sessions;
};

#endif //CONTINUUM_GENERAL_H