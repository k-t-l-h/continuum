#include "pch.h"

TEST_F(WebTestCase, DCreateTest)
{
	//по дефолту
	WebTestCase c();
	ASSERT_EQ(c.id, 0);
	ASSERT_EQ(c.host, "localhost");
	ASSERT_EQ(c.p, HTTP);
	ASSERT_EQ(c.m, GET);
	ASSERT_EQ(c.reference, 200);
}

TEST_F(WebTestCase, CreateTestI)
{
	WebTestCase c(2);
	ASSERT_EQ(c.id, 2);
	ASSERT_EQ(c.host, "localhost");
	ASSERT_EQ(c.p, HTTP);
	ASSERT_EQ(c.m, GET);
	ASSERT_EQ(c.reference, 200);
}

TEST_F(WebTestCase, CreateTestII)
{
	WebTestCase c(2, "adress", POST);
	ASSERT_EQ(c.id, 2);
	ASSERT_EQ(c.host, "adress");
	ASSERT_EQ(c.p, HTTP);
	ASSERT_EQ(c.m, POST);
	ASSERT_EQ(c.reference, 200);
}

TEST_F(WebTestCase, CreateTestIII)
{
	std::string fileName = "test.csv";
	int I = get_i(fileName);
	std::string A = get_adress(fileName);
	int P = get_protocol(fileName);
	int M = get_method(fileName);
	int  R= get_ref(fileName);

	WebTestCase c(I, A, P, M, R);
	ASSERT_EQ(c.id, I);
	ASSERT_EQ(c.host, A);
	ASSERT_EQ(c.p, P);
	ASSERT_EQ(c.m, M);
	ASSERT_EQ(c.reference, R);

}
