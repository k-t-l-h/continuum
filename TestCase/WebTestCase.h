#ifndef WEB_TEST_CASE_H
#define WEB_TEST_CASE_H


#include <string>
#include "TestCaseClass.h"

class WebTestCase : public TestCase {
public:
    WebTestCase();

    WebTestCase(std::string _id, std::string _host, int _p, int _m, int _reference) :
            id(_id), rtype(1), host(_host), p(_p), m(_m), reference(_reference) {};

    WebTestCase(const WebTestCase &) = delete;

    WebTestCase operator=(const WebTestCase &) = delete;

    ~WebTestCase() {};

    std::string id;
    int rtype;
    std::string host;

    enum protocol {
        HTTP, HTTPS
    };
    enum method {
        OPTIONS, GET, POST, PUT, DELETE
    };

    int p;
    int m;
    int reference;
};

#endif //WEB_TEST_CASE_H
