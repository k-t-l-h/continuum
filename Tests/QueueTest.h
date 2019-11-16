#include "../Queue/Queue.h"

#include "gtest/gtest.h"
#include <boost/thread/thread.hpp>

using ::testing::AtLeast;

class TestQueue : public ::testing::Test
{
protected:
	void SetUp()
	{
		queue = new Queue<int>();
	}
	
	void TearDown()
	{
		delete queue;
	}
	Queue *queue;
}

void f1(Queue *q)
{
	for (int i = 0; i < 20; i+=2) {
		q.push(i);
		sleep(2);
	}
}

void f2(Queue *q)
{
	sleep(1);
	for (int i = 1; i < 20; i+=2) {
		q.push(i);
		sleep(2);
	}
}

TEST_F(TestQueue, TestSafety)
{
	boost::thread t1(f1(queue));
	boost::thread t2(f2(queue));
	t1.join()
	t2.join()
	bool flag = true;
	int last = queue.pop();
	for( int i = 1; i < 20; i++ ) {
		int tmp = queue.pop();
		if (last < tmp) {
			flag = false;
			break;
		}
		last = tmp;
	}
	ASSERT_TRUE(flag);
}