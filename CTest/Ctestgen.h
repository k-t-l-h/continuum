#ifndef CTESTGENERATION_H
#define CTESTGENERATION_H

#include "../TestGeneration/Testgen.h"
#include "../Queue/Queue.h"
#include "../TestCase/CTestCase.h"
#include "../TestCase/TestCaseClass.h"

#include <memory>
#include <string>


class CTestGeneration: public AbstractTestGeneration
{
public:
 CTestGeneration() = delete;
 CTestGeneration(const CTestGeneration&) = delete;
 CTestGeneration operator=(const CTestGeneration&) = delete;

 CTestGeneration(const std::string request, std::shared_ptr<Queue<TestCase*>> _wque);

 void convertToTestCase() override;
 int sendToWorker() const override;

  private:
    std::shared_ptr<Queue<TestCase*>> wque;
    CTestCase *tcase;
    std::string request;
};

#endif //CTESTGENERATION_H
