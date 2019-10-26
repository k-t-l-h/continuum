//
// Created by evgeny on 26.10.2019.
//

#include "TestWorker.h"

#include "gtest/gtest.h"

class Tests : public ::testing::Test
{
protected:
    void SetUp()
    {
        int n;
        q = db();
        w = Worker(Queue, n);
    }
    void TearDown()
    {

    }

    db q;
    Worker w;
};

TEST_F(Tests, test1)
{

}

TEST_F(Tests, test2)
{

}
