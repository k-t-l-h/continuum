#ifndef WEB_TEST_CASE_H
#define WEB_TEST_CASE_H


#include <string>
#include "TestCaseClass.h"

class WebTestCase : public TestCase {
public:
    WebTestCase();

    WebTestCase(std::string id, std::string host, int p, int m, int reference) :
            id(id), rtype(1), host(host), p(p), m(m), reference(reference) {};

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
