//
// Created by evgeny on 26.10.2019.
//

#include "../Reporter/Reporter.cpp"

#include "gtest/gtest.h"

TEST(TestManager, TestGetDB) {
    DataBase db;
    Queue<std::string> queue;
    Reporter<std::string> reporter(queue, db);
    EXPECT_TRUE(&db == &reporter.GetDB());
}

TEST(TestManager, TestGetQueue) {
    DataBase db;
    Queue<std::string> queue;
    Reporter<std::string> reporter(queue, db);
    EXPECT_TRUE(&queue == &reporter.GetQueue());
}
