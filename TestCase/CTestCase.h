#ifndef CTEST_CASE_H
#define CTEST_CASE_H

using namespace std;

class CTestCase: public TestCase
{
public:
  CTestCase();
  CTestCase(int id, string git_adress, string target);
  ~CTestCase();

  CTestCase(const CTestCase&) = delete;
  CTestCase operator=(const CTestCase&) = delete;

  int id;
  string git_adress;
  string target;
};

#endif //CTEST_CASE_H
