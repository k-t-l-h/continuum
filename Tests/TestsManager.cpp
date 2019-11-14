#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../Manager/Manager.h"

using ::testing::AtLeast;

template <class T>
struct MockQueue : Queue<T> {

    MOCK_CONST_METHOD0(empty, bool());

};


TEST(MockCantainer, TestWorkCycleCallEmpty) {
    int n = 5;
    MockQueue<TestCase *> QueueIn;
    Queue<std::string> QueueOut;
    Manager manager(QueueIn, QueueOut, n);
    EXPECT_CALL(QueueIn, empty()).Times(AtLeast(1));
    manager.WorkCycle();
}
