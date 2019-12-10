#ifndef TEST_CASE_CLASS_H
#define TEST_CASE_CLASS_H

using namespace std;

#include <string>

class TestCase
{
public:
  //virtual TestCase() =0;
  virtual ~TestCase() {}
  string id;
  int rtype;
};

#endif //TEST_CASE_CLASS_H
