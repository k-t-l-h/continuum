#ifndef PARSER_H
#define PARSER_H

using namespace std;

class Parser
{
    public:
      Parser() = delete;
      Parser(const Parser&) = delete;
      Parser operator=(const Parser&) = delete;

      Parser(shared_ptr<Queue<std::string>> _rque,
      shared_ptr<Queue<TestCase*>> _wque,
      shared_ptr<Queue<std::string>> _reque);

      ~Parser();
      void workCycle() const;

    private:
      std::string& get_request() const;
      void workThread(const std::string& s);
      bool validateRequest(const std::string &request) const;

      bool validateHost(const std::string& s) const;
      bool validateAdress(const std::string& s) const;
      bool validateMethod(const std::string& s) const;
      bool validateTarget(const std::string& s) const;
      bool validateRequest(const std::string& s) const;
      bool validateProtocol(const std::string& s) const;
      bool validateReference(const std::string& s) const;

      shared_ptr<Queue<std::string>> rque;
      shared_ptr<Queue<TestCase*>> wque;
      shared_ptr<Queue<std::string>> reque;

};

#endif //PARSER_H
