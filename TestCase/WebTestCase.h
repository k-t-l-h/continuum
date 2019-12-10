#ifndef WEB_TEST_CASE_H
#define WEB_TEST_CASE_H

using namespace std;

#include <string>
#include "TestCaseClass.h"

class WebTestCase: public TestCase
{
public:
  WebTestCase();
  WebTestCase(string _id, string _host, int _p, int _m, int _reference):
  id(_id), rtype(1), host(_host), p(_p), m(_m), reference(_reference){};

  WebTestCase(const WebTestCase&) = delete;
  WebTestCase operator=(const WebTestCase&) = delete;

  ~WebTestCase(){};

  string id;
  int rtype;
  string host;

  enum protocol {HTTP, HTTPS};
  enum method {OPTIONS, GET, POST, PUT, DELETE};

  int p;
  int m;
  int reference;
};

#endif //WEB_TEST_CASE_H
