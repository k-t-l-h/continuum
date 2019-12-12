#ifndef PARSER_H
#define PARSER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/regex.hpp>

#include "../Queue/Queue.h"
#include "../TestCase/TestCaseClass.h"
#include "../TestCase/CTestCase.h"
#include "../TestCase/WebTestCase.h"
#include "../TestGeneration/Testgen.h"
#include "../CTest/Ctestgen.h"
#include "../WebTest/Webtestgen.h"

#include <memory>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <functional>


namespace pt = boost::property_tree;

//глобальные переменные
std::mutex m;
std::mutex pmutex;
std::condition_variable condition;
bool notified;

class Parser
{
    public:
      Parser() = delete;
      Parser(const Parser&) = delete;
      Parser operator=(const Parser&) = delete;

      Parser(std::shared_ptr<Queue<std::string>> _rque,
      std::shared_ptr<Queue<TestCase*>> _wque,
      std::shared_ptr<Queue<std::string>> _reque);

      ~Parser();
      void workCycle() const;
      void setStatus(bool newStatus);

    private:
      bool workStatus;
      unsigned int maxPool;

      std::vector<thread> threadPool;

      std::string get_request() const;
      void workThread(const std::string& s);
      bool validateRequest(const pt::ptree tree) const;

      bool validateHost(const std::string& s) const;
      bool validateAdress(const std::string& s) const;
      bool validateMethod(const std::string& s) const;
      bool validateTarget(const std::string& s) const;
      bool validateRequest(const std::string& s) const;
      bool validateProtocol(const std::string& s) const;
      bool validateReference(const std::string& s) const;

      std::shared_ptr<Queue<std::string>> rque;
      std::shared_ptr<Queue<TestCase*>> wque;
      std::shared_ptr<Queue<std::string>> reque;

      struct ResponseCode {
        static const std::string OK = "0";
        static const std::string invalidRequestStructure = "Invalid structute";
        static const std::string defaultId = "Invalid ID";

        static const int invalidRequestType = -1;
        static const int cppRequestType =  0;
        static const int webRequestType = 1;

        static const std::string defaultHost = "Invalid host";
        static const std::string defaultProtocol = "Invalid protocol";
        static const std::string defaultMethod = "Invalid method";
        static const std::string defaultReference = "Invalid Reference";

        static const std::string defaultTarget = "Invalid Target";
        static const std::string defaultGit = "Invalid Git Adress";

        const std::string temporary = "Sorry";
      } codes;

};

#endif //PARSER_H
