#ifndef TEST_CASE_CLASS_H
#define TEST_CASE_CLASS_H

class TestCase
{
public:
  //virtual TestCase() =0;
  virtual ~TestCase() =0;
  string id;
  int rtype;
};

#endif //TEST_CASE_CLASS_H
