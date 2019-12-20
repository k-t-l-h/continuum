#include "../Container/Container.h"
#include "../TestCase/TestCase.h"

#include "gtest/gtest.h"
#include <boost/thread/thread.hpp>

using ::testing::AtLeast;

class TestContainer : public ::testing::Test
{
protected:
	void SetUp()
	{
		rq = std::make_shared<Queue<std::string>>();
		container = new Container(rq);
	}
	
	void TearDown()
	{
		delete container;
		delete rq;
	}
	Container *container;
	Queue<JsonObject> *rq;
}

TEST_F(TestContainer, ContainerBusy)
{
	// some testcase
    auto *test = new WebTestCase("qwerty", "github.com", 0, 1, 0);
	
	boost::thread t(container.DoTest(test));
	ASSERT_FALSE(container.IsFree());
	t.join()
}

TEST_F(TestContainer, ContainerFree)
{
	ASSERT_TRUE(container.IsFree());
}

TEST_F(TestContainer, CorrectTestSent)
{
	// correct testcase
	auto *test = new WebTestCase("qwerty", "github.com", 0, 1, 0);
	ASSERT_EQ(container.DoTest(test), OK);
}

TEST_F(TestContainer, IncorrectTestNotSent)
{
	// incorrect testcase
    auto *test = new WebTestCase("qwerty", "sgasdjdh", 0, 1, 0);
	
	ASSERT_EQ(container.DoTest(test), DOCKER_ERR);
}

TEST_F(TestContainer, RightAnswer)
{
	// correct answer
	std::string answer = "HTTP/1.1 301 Moved Permanently\r\nContent-length: 0\r\nLocation: https://github.com/\r\n\r\n"

	
	container.doTest(test);
	ASSERT_EQ(container.getAnswer(), answer);
}
