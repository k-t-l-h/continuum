#include "pch.h"

TEST_F(WebTestGeneration, DCreateTest)
{
	//не создается по дефолту
	ASSERT_NO_THROW(WebTestGeneration c());
}

TEST_F(CTestCase, CreateTestI)
{
	ASSERT_ANY_THROW(WebTestGeneration c(NULL, NULL));

}

TEST_F(CTestCase, CreateTestII)
{
	ASSERT_ANY_THROW(WebTestGeneration c(NULL, Queque q));

}

TEST_F(CTestCase, CreateTestIII)
{
	ASSERT_ANY_THROW(WebTestGeneration c(request r, NULL));

}

TEST_F(CTestCase, CreateTestIV)
{
	ASSERT_NO_THROW(WebTestGeneration c(request r, Queque q));

}

TEST_F(CTestCase, ConvertTest)
{
	WebTestGeneration c(request r, Queque q);
	ASSERT_NE(c.convert(r), NULL);
}

TEST_F(CTestCase, SendTest)
{
	WebTestGeneration c(request r, Queque q);
	ASSERT_EQ(c.send(c.tcase, c.q), 0);
}
