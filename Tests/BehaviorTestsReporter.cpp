#include "../Reporter/Reporter.cpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::AtLeast;

struct MockDataBase : DataBase {

    MOCK_CONST_METHOD0(GetSize, int());

};

template <class T>
struct MockQueue : Queue<T> {

    MOCK_CONST_METHOD0(empty, bool());

};

TEST(MockDataBase, TestPutInDB) {
    DataBase db;
    Queue<std::string> queue;
    int size = db.GetSize();
    Reporter<std::string> reporter(queue, db);
    reporter.PutInDB("Hello");
    EXPECT_TRUE(db.GetSize() == size + 1);
}

TEST(MockDataBase, TestWorkVycle) {
    DataBase db;
    MockQueue<std::string> queue;
    Reporter<std::string> reporter(queue, db);
    EXPECT_CALL(queue, empty()).Times(AtLeast(1));
    reporter.WorkCycle();
}

