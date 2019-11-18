#ifndef WEB_TEST_CASE_H
#define WEB_TEST_CASE_H


class WebTestCase: public TestCase
{
public:
  WebTestCase();
  WebTestCase(int id, std::string host, protocol p, method m, int reference);
  WebTestCase(int id, std::string host, enum method); //по умолчанию HTTP и ответ 200
  explicit WebTestCase(int id);

  WebTestCase(const WebTestCase&) = delete;
  WebTestCase operator=(const WebTestCase&) = delete;

  ~WebTestCase();

  int id;
  std::string host;

  enum protocol {HTTP, HTTPS};
  enum method {OPTIONS, GET, POST, PUT, DELETE};

  protocol p;
  method m;
  int reference;
};


#endif WEB_TEST_CASE_H
