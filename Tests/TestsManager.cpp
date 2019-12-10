#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../Manager/Manager.h"

using ::testing::AtLeast;

template <class T>
struct MockQueue : public Queue<T> {

    MOCK_CONST_METHOD0(empty, bool());

    MOCK_METHOD(T, front, (), (override));

    MOCK_METHOD(void, pop, (), (override));

};

TEST(MockCantainer, TestWorkCycleCallEmpty) {
    int n = 5;
    MockQueue<TestCase *> *QueueIn;
    MockQueue<JsonObject> *QueueOut;
    Manager manager(QueueIn, QueueOut, n);
    EXPECT_CALL(*QueueIn, empty()).Times(AtLeast(1));
    manager.WorkCycle();
}
/*
TEST(MockCantainer, TestWorkCycleCountContainers) {
    int n = 5;
    MockQueue<TestCase *> QueueIn;
    Queue<std::string> QueueOut;
    Manager manager(QueueIn, QueueOut, n);
    EXPECT_TRUE(manager.GetCountContainers() == n);
}*/
/*
TEST(MockCantainer, TestCreateContainers) {
    int n = 5;
    MockQueue<TestCase *> QueueIn;
    Queue<std::string> QueueOut;
    Manager manager(QueueIn, QueueOut, n);
    std::vector<Container *> containers = manager.GetContainers();
    for (int i = 0; i < n; ++i)
        EXPECT_TRUE(containers[i]->IsFree() == true);
}*/


