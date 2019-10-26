class WebTestGeneration: public AbstractTestGeneration
{
public:
  WebTestGeneration();
  WebTestGeneration(JsonObject request, Queque* wque);
  ~WebTestGeneration();

  TestCase convert(JsonObject request);
  int sendToWorker(TestCase tcase, Queque* wque);

private:
  Queque* wque;

  TestCase tcase;
  JsonObject request;

};
