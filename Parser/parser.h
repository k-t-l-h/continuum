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

      void workCycle();

    private:
      std::string& get_request();
      bool validateRequest(const std::string &request);

      bool validateHost(const std::string& s);
      bool validateAdress(const std::string& s);
      bool validateMethod(const std::string& s);
      bool validateTarget(const std::string& s);
      bool validateRequest(const std::string& s);
      bool validateProtocol(const std::string& s);
      bool validateReference(const std::string& s);

      Queue* pque;
      Queue* wque;
};

#endif //PARSER_H
