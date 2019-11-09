#include "gtest/gtest.h"
#include "../TestCase/CTestCase.h"

TEST_F(CTestCase, DCreateTest)
{
	CTestCase c();
	ASSERT_EQ(c.id, 0);
	ASSERT_EQ(c.git_adress, "");
	ASSERT_EQ(c.target, "all");
}

TEST_F(CTestCase, CreateTestI)
{
	CTestCase c(2, "", "");
	ASSERT_EQ(c.id, 2);
	ASSERT_EQ(c.git_adress, "");
	ASSERT_EQ(c.target, "all");
}

TEST_F(CTestCase, CreateTestII)
{
	CTestCase c(2, "adress", "main");
	ASSERT_EQ(c.id, 2);
	ASSERT_EQ(c.git_adress, "adress");
	ASSERT_EQ(c.target, "main");

}

TEST_F(CTestCase, CreateTestIII)
{
	CTestCase c(2, "", "main");
	ASSERT_EQ(c.id, 2);
	ASSERT_EQ(c.git_adress, "adress");
	ASSERT_EQ(c.target, "main");

}

TEST_F(CTestCase, CreateTestIV)
{
	std::string fileName = "test.csv";
	int id = get_id(fileName);
	std::string adress = get_adress(fileName);
	std::string target = get_adress(fileName);
	CTestCase c(id, adress, target);
	ASSERT_EQ(c.id, id);
	ASSERT_EQ(c.git_adress, adress);
	ASSERT_EQ(c.target, target);
}
