#ifndef TEST_GENERATION_H
#define TEST_GENERATION_H


class AbstractTestGeneration
{
    public:
      //virtual AbstractTestGeneration() =0; //конструктор
      //virtual AbstractTestGeneration(const string req, Queue<TestCase> &wque)) =0;
      virtual ~AbctractTestGeneration() {}; //декструктор

      void convertToTestCase() =0;
      int sendToWorker() const =0;

};

#endif //TEST_GENERATION_H
