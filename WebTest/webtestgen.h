#ifndef WEB_TEST_GENERATION_H
#define WEB_TEST_GENERATION_H

using namespace std;
namespace pt = boost::property_tree;

class WebTestGeneration: public AbstringactTestGeneration
{
public:
  WebTestGeneration() = delete;
  WebTestGeneration(const string request, Queue<TestCase*> &wque);
  WebTestGeneration(const CTestGeneration&) = delete;
  WebTestGeneration operator=(const CTestGeneration&) = delete;
  ~WebTestGeneration();

  void convertToTestCase() override;
  int sendToWorker() const override;

private:
  Queque* wque;
  WebTestCase tcase;
  JsonObject request;

};

#endif //WEB_TEST_GENERATION_H
