//
// Created by David on 06/07/2024.
//
#include "gtest/gtest.h"
#include "Queue.hpp"

class QueueTest : public ::testing::Test {
protected:
    Queue<int> queue;
    int data[2] = {1, 2};
    void SetUp() override {
        queue = Queue<int>();
    }
};

TEST_F(QueueTest, IsEmptyInitially) {
    EXPECT_TRUE(queue.isEmpty());
}

TEST_F(QueueTest, NotEmptyAfterEnqueue) {
    queue.enqueue(data[0]);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_EQ(queue.getNodeCount(),1);
}

TEST_F(QueueTest, IsEmptyAfterEnqueueAndDequeue) {
    queue.enqueue(data[0]);
    queue.dequeue();
    EXPECT_TRUE(queue.isEmpty());
}

TEST_F(QueueTest, EnqueueMultipleElements) {
    queue.enqueue(data[0]);
    queue.enqueue(data[1]);
    EXPECT_EQ(*queue.getDataAtNode(0), 1);
    EXPECT_EQ(*queue.getDataAtNode(1), 2);
    EXPECT_EQ(queue.getNodeCount(),2);
}

TEST_F(QueueTest, DequeueFromEmptyQueue) {
    testing::internal::CaptureStdout();
    queue.dequeue();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Can't dequeue, queue is empty\n");
    EXPECT_TRUE(queue.isEmpty());
}