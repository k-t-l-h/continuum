class WebTestGeneration: public AbstractTestGeneration
{
public:
  TestCase convert(JsonObject request);
  int sendToWorker(TestCase tcase, Queque* wque);

private:
  Queque* wque;

  TestCase tcase;
  JsonObject request;

};
