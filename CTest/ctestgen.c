class CTestGeneration: public AbstractTestGeneration
{
  public:
    CTestGeneration();
    CTestGeneration(Queue* rque, Queue* wque);

    ~CTestGeneration();

    TestCase convert(JsonObject request);
    int sendToWorker(TestCase tcase, Queue* wque);

  private:
    Queue* wque;

    TestCase tcase;
    JsonObject request;
};
