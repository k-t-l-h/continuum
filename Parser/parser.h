#ifndef PARSER_H
#define PARSER_H



#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <mutex>
#include <atomic>
#include <condition_variable>
#include <thread>

using namespace std;

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
      atomic_uint sizePool;
      unsigned int maxPool;

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

        const strinf invalidRequestType = "Untyped request";
        const string cppRequestType = "CPP";
        const string webRequestType = "WEB";

        const string defaultHost = "Invalid host";
        const string defaultProtocol = "Invalid protocol";
        const string defaultMethod = "Invalid method";
        const string defaultReference = "Invalid Reference";

        const string defaultTarget = "Invalid Target";
        const string defaultGit = "Invalid Git Adress";

        const string temporary = "Sorry";
      };

};

#endif //PARSER_H
