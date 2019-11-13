class WebTestGeneration: public AbstractTestGeneration
{
public:
  WebTestGeneration() = delete;
  WebTestGeneration(const JsonObject &request, Queue<TestCase*> &wque);
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
