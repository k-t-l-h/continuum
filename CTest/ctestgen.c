class CTestGeneration: public AbstractTestGeneration
{
  public:
    CTestGeneration();
    CTestGeneration(Queue* rque, Queue* wque);

    ~CTestGeneration();

    void convert(JsonObject &request) override;
    int sendToWorker(TestCase &tcase, Queue* wque) override;

  private:
    Queue* wque;

    TestCase tcase;
    JsonObject request;
};
