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

      void work();

    private:
      bool validateRequest();
      int getRequestType();
      
      Queue* pque;
      Queue* wque;
};

#endif //PARSER_H
