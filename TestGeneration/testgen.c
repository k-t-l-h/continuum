//SingleTon
class AbctractTestGeneration
{
  public:
    virtual AbctractTestGeneration();
    virtual ~AbctractTestGeneration();
    
    virtual JsonObject getRequest(Queue* rque) =0;
    virtual TestCase convert(JsonObject request) =0;
    virtual int sendToWorker(TestCase tcase, Queque* wque) =0;

  private:
    Queque* rque;
    Queque* wque;

    TestCase tcase;
    JsonObject request;
};
