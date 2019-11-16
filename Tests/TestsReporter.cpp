#include "../Reporter/Reporter.h"

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

TEST(TestReporter, TestPutInDB) {
    DataBase db;
    Queue<JsonObject> queue;
    Reporter<JsonObject> reporter(queue, db);
    JsonObject json;
    reporter.PutInDB(json);
    EXPECT_TRUE(reporter.PutInDB(json) == true);
}

TEST(TestReporter, TestNotify) {
    DataBase db;
    Queue<JsonObject> queue;
    int size = db.GetSize();
    Reporter<JsonObject> reporter(queue, db);
    JsonObject json;
    reporter.PutInDB(json);
    EXPECT_TRUE(reporter.PutInDB(json) == true);
}

TEST(TestReporter, CallEmpty) {
    DataBase db;
    MockQueue<JsonObject> queue;
    Reporter<JsonObject> reporter(queue, db);
    EXPECT_CALL(queue, empty()).Times(AtLeast(1));
    reporter.WorkCycle();
}