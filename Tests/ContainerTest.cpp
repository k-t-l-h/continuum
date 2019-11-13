#include "../Container/Container.cpp"
#include "../TestCase/TestCase.cpp"

#include "gtest/gtest.h"
#include <boost/thread/thread.hpp>

using ::testing::AtLeast;

class TestContainer : public ::testing::Test
{
protected:
	void SetUp()
	{
		container = new Container();
	}
	
	void TearDown()
	{
		delete container;
	}
	Container *container;
}

TEST_F(TestContainer, ContainerBusy)
{
	// some testcase
	TestCase test();
	
	boost::thread t(container.DoTest(test));
	ASSERT_FALSE(container.IsFree());
	t.join()
}

TEST_F(TestContainer, ContainerFree)
{
	ASSERT_TRUE(container.IsFree());
}

TEST_F(TestContainer, HasHost)
{
	ASSERT_TRUE(container.GetContainerHost() != nullptr);
}

TEST_F(TestContainer, CorrectTestSent)
{
	// correct testcase
	TestCase test();
	ASSERT_EQ(container.DoTest(test), OK);
}

TEST_F(TestContainer, IncorrectTestNotSent)
{
	// incorrect testcase
	TestCase test();
	
	ASSERT_EQ(container.DoTest(test), ERROR);
}

TEST_F(TestContainer, RightAnswer)
{
	// correct answer
	JsonObject answer;
	TestCase test();
	
	container.DoTest(test);
	ASSERT_EQ(container.GetAnswer(), answer);
}
