#ifndef WEB_TEST_GENERATION_H
#define WEB_TEST_GENERATION_H

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

#endif //WEB_TEST_GENERATION_H
