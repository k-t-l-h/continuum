#ifndef CTESTGENERATION_H
#define CTESTGENERATION_H

class CTestGeneration: public AbstractTestGeneration
{
  public:
    CTestGeneration() = delete;
    CTestGeneration(const JsonObject request, Queue<TestCase> &wque);
    CTestGeneration(const CTestGeneration&) = delete;
    CTestGeneration operator=(const CTestGeneration&) = delete;
    ~CTestGeneration();

    void convert() override;
    int sendToWorker() override;

  private:
    Queue* wque;

    CTestCase tcase;
    JsonObject request;
};

#endif CTESTGENERATION_H
