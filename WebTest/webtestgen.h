#ifndef WEB_TEST_GENERATION_H
#define WEB_TEST_GENERATION_H

using namespace std;
namespace pt = boost::property_tree;

class WebTestGeneration: public AbstringactTestGeneration
{
public:
  WebTestGeneration() = delete;
  WebTestGeneration(const CTestGeneration&) = delete;
  WebTestGeneration operator=(const CTestGeneration&) = delete;
  
  WebTestGeneration(const str request,   shared_ptr<Queue<TestCase*>> _wque);
  ~WebTestGeneration();

  void convertToTestCase() override;
  int sendToWorker() const override;

private:
  shared_ptr<Queue<TestCase*>> wque;
  WebTestCase tcase;
  string request;

};

#endif //WEB_TEST_GENERATION_H
