#ifndef CTEST_CASE_H
#define CTEST_CASE_H

#include "TestCaseClass.h"
#include <string>


class CTestCase : public TestCase {
public:
    CTestCase(std::string id, std::string git_adress, std::string target) :
            id(id), rtype(0), git_adress(git_adress), target(target) {};

    ~CTestCase() {};

    CTestCase(const CTestCase &) = delete;

    CTestCase operator=(const CTestCase &) = delete;

    std::string id;
    int rtype;
    std::string git_adress;
    std::string target;
};

#endif //CTEST_CASE_H
