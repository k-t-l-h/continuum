class WebTestGeneration: public AbstractTestGeneration
{
public:
  WebTestGeneration();
  WebTestGeneration(JsonObject request, Queque* wque);
  ~WebTestGeneration();

  TestCase convert(JsonObject request) override;
  int sendToWorker(TestCase tcase, Queque* wque) override;

private:
  Queque* wque;

  TestCase tcase;
  JsonObject request;

};
