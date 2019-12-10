#ifndef PARSER_H
#define PARSER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../Queue/Queque.h"
#include "../TestCase/TestCaseClass.h"
#include "../TestCase/CTestCase.h"
#include "../TestCase/WebTestCase.h"
#include "../TestGeneration/testgen.h"
#include "../CTest/ctestgen.h"
#include "../WebTest/webtestgen.h"

#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <functional>

using namespace std;
namespace pt = boost::property_tree;

mutex pmutex;
//глобальные переменные
mutex m;
condition_variable condition;
bool notified;

class Parser
{
    public:
      Parser() = delete;
      Parser(const Parser&) = delete;
      Parser operator=(const Parser&) = delete;

      Parser(shared_ptr<Queue<string>> _rque,
      shared_ptr<Queue<TestCase*>> _wque,
      shared_ptr<Queue<string>> _reque);

      ~Parser();
      void workCycle() const;
      void setStatus();

    private:
      bool workStatus;
      unsigned int maxPool;

      vector<thread> threadPool;

      string& get_request() const;
      void workThread(const string& s);
      bool validateRequest(const string &request) const;

      bool validateHost(const string& s) const;
      bool validateAdress(const string& s) const;
      bool validateMethod(const string& s) const;
      bool validateTarget(const string& s) const;
      bool validateRequest(const string& s) const;
      bool validateProtocol(const string& s) const;
      bool validateReference(const string& s) const;

      shared_ptr<Queue<string>> rque;
      shared_ptr<Queue<TestCase*>> wque;
      shared_ptr<Queue<string>> reque;

      struct ResponseCode {
        const string OK = "0";
        const string invalidRequestStructure = "Invalid structute";
        const string defaultId = "Invalid ID";

        const int invalidRequestType = -1;
        const int cppRequestType =  0;
        const int webRequestType = 1;

        const string defaultHost = "Invalid host";
        const string defaultProtocol = "Invalid protocol";
        const string defaultMethod = "Invalid method";
        const string defaultReference = "Invalid Reference";

        const string defaultTarget = "Invalid Target";
        const string defaultGit = "Invalid Git Adress";

        const string temporary = "Sorry";
      } codes;

};

#endif //PARSER_H
