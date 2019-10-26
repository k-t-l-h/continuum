class CTestCase: public TestCase
{
public:
  CTestCase();
  CTestCase(int id, std::string git_adress, std::string target);
  ~CTestCase();

  int id;
  std::string git_adress;
  std::string target;
};
