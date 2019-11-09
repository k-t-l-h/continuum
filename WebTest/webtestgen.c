class WebTestGeneration: public AbstractTestGeneration
{
public:
  WebTestGeneration();
  WebTestGeneration(JsonObject &request, Queque* wque);
  ~WebTestGeneration();

  void convert(JsonObject &request) override;
  int sendToWorker(TestCase &tcase) override;

private:
  Queque* wque;
  TestCase tcase;
  JsonObject request;

};
