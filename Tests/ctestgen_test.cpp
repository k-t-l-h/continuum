#include "pch.h"

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
