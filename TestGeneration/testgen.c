class AbstractTestGeneration
{
  public:
    virtual AbstractTestGeneration();
    virtual AbstractTestGeneration(JsonObject request, Queue* wque)
    virtual ~AbctractTestGeneration();
    
    virtual TestCase convert(JsonObject request) =0;
    virtual int sendToWorker(TestCase tcase, Queue* wque) =0;

  private:
    Queue* wque;

    TestCase tcase;
    JsonObject request;
};
