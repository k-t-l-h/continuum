#ifndef WEB_TEST_GENERATION_H
#define WEB_TEST_GENERATION_H

class WebTestGeneration: public AbstractTestGeneration
{
public:
  WebTestGeneration() = delete;
  WebTestGeneration(const JsonObject &request, const Queue<TestCase*> &wque);
  WebTestGeneration(const CTestGeneration&) = delete;
  WebTestGeneration operator=(const CTestGeneration&) = delete;
  ~WebTestGeneration();

  void convert(JsonObject const &request) override;
  int sendToWorker(TestCase &tcase) override;

private:
  Queque* wque;
  WebTestCase tcase;
  JsonObject request;

};

#endif //WEB_TEST_GENERATION_H
