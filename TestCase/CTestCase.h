#ifndef CTEST_CASE_H
#define CTEST_CASE_H

#include "TestCaseClass.h"
#include <string>


class CTestCase : public TestCase {
public:
    CTestCase(std::string _id, std::string _git_adress, std::string _target) :
            id(_id), rtype(0), git_adress(_git_adress), target(_target) {};

    ~CTestCase() {};

    CTestCase(const CTestCase &) = delete;

    CTestCase operator=(const CTestCase &) = delete;

    std::string id;
    int rtype;
    std::string git_adress;
    std::string target;
};

#endif //CTEST_CASE_H
