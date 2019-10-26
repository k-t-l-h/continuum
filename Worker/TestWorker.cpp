//
// Created by evgeny on 26.10.2019.
//

#include "Worker.h"

#include "gtest/gtest.h"

class Tests : public ::testing::Test
{
protected:
    void SetUp()
    {
        q = Queue(n);
        w = Reporter(Queue, n);
    }
    void TearDown()
    {

    }
    Queue q;
    Worker w;
};

TEST_F(Tests, test1)
{

}

TEST_F(Tests, test2)
{

}