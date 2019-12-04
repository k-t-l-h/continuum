#ifndef CTESTGENERATION_H
#define CTESTGENERATION_H

using namespace std;

class CTestGeneration: public AbstractTestGeneration
{
  public:
    CTestGeneration() = delete;
    CTestGeneration(const CTestGeneration&) = delete;
    CTestGeneration operator=(const CTestGeneration&) = delete;

    CTestGeneration(const str request,   shared_ptr<Queue<TestCase*>> _wque);
    ~CTestGeneration();

    void convertToTestCase() override;
    int sendToWorker() const override;

  private:
    shared_ptr<Queue<TestCase*>> wque;
    CTestCase tcase;
    string request;
};

#endif CTESTGENERATION_H
