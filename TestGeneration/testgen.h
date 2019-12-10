#ifndef TEST_GENERATION_H
#define TEST_GENERATION_H


class AbstractTestGeneration
{
    public:
      //virtual AbstractTestGeneration() =0; //конструктор
      //virtual AbstractTestGeneration(const string req, Queue<TestCase> &wque)) =0;
      virtual ~AbstractTestGeneration(); //декструктор

      virtual void convertToTestCase() =0;
      virtual int sendToWorker() const =0;

};

#endif //TEST_GENERATION_H
