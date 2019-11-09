//
// Created by evgeny on 26.10.2019.
//

#include "../Manager/Manager.cpp"

#include "gtest/gtest.h"


TEST(TestManager, TestGetCountContainers) {
    int n = 5;
    Queue<TestCase *> queue;
    Manager manager(queue, n);
    ASSERT_EQ(n, manager.GetCountContainers());
}

TEST(TestManager, TestGetQueue) {
    int n = 5;
    Queue<TestCase *> queue;
    Manager manager(queue, n);
    EXPECT_TRUE(&queue == &manager.GetQueue());
}

TEST(TestManager, TestGetContainers) {
    int n = 5;
    Queue<TestCase *> queue;
    Manager manager(queue, n);
    EXPECT_TRUE(manager.GetContainers().size() == n);
}
