#ifndef PARSER_H
#define PARSER_H

class Parser
{
    public:
      Parser() = delete;
      Parser(Queue<Request*> &pque, Queue<TestCase*> &wque);
      Parser(const Parser&) = delete;
      Parser operator=(const Parser&) = delete;
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

      Queue* rque;
      Queue* wque;
};

#endif //PARSER_H
