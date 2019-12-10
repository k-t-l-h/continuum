#ifndef TEST_CASE_CLASS_H
#define TEST_CASE_CLASS_H

#include <string>

class TestCase
{
public:
  //virtual TestCase() =0;
  virtual ~TestCase() {}
  std::string id;
  int rtype;
};

#endif //TEST_CASE_CLASS_H
