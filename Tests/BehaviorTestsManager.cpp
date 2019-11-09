#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../Manager/Manager.h"

using ::testing::AtLeast;

template <class T>
struct MockQueue : Queue<T> {

    MOCK_CONST_METHOD0(empty, bool());

};

TEST(MockCantainer, TestWorkCycle) {
    int n = 5;
    MockQueue<TestCase *> queue;
    Manager manager(queue, n);
    EXPECT_CALL(queue, empty()).Times(AtLeast(1));
    manager.WorkCycle();
}
