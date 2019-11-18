#ifndef CTEST_CASE_H
#define CTEST_CASE_H

class CTestCase: public TestCase
{
public:
  CTestCase();
  CTestCase(int id, std::string git_adress, std::string target);
  ~CTestCase();

  CTestCase(const CTestCase&) = delete;
  CTestCase operator=(const CTestCase&) = delete;

  int id;
  std::string git_adress;
  std::string target;
};

#endif //CTEST_CASE_H
