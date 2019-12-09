#ifndef CTEST_CASE_H
#define CTEST_CASE_H

#include "TestCaseClass.h"
#include <string>

using namespace std;

class CTestCase: public TestCase
{
public:
  CTestCase(string _id, string _git_adress, string _target):
  id(_id), rtype(0), git_adress(_git_adress), target(_target);
  ~CTestCase();

  CTestCase(const CTestCase&) = delete;
  CTestCase operator=(const CTestCase&) = delete;

  string id;
  int rtype;
  string git_adress;
  string target;
};

#endif //CTEST_CASE_H
