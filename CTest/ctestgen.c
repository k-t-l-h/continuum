class WebTestGeneration: public AbstractTestGeneration
{
  public:
    WebTestGeneration();
    WebTestGeneration(Queue* rque, Queue* wque)
    ~WebTestGeneration();

    TestCase convert(JsonObject request);
    int sendToWorker(TestCase tcase, Queue* wque);

  private:
    Queue* wque;

    TestCase tcase;
    JsonObject request;
};
