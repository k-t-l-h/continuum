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
      bool validateRequest();

      bool validateHost();
      bool validateAdress();
      bool validateMethod();
      bool validateTarget();
      bool validateRequest();
      bool validateProtocol();
      bool validateReference();

      Queue* pque;
      Queue* wque;
};

#endif //PARSER_H
