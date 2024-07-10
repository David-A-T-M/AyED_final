//
// Created by David on 06/07/2024.
//
#include "gtest/gtest.h"
#include "Queue.hpp"
#include "Packet.hpp"

class QueueTest : public ::testing::Test {
protected:
    IPAddress ip{170, 0b10101010};
    Queue<Packet> *pQueueEmpty{}, *pQueueWith1{}, *pQueueWith3{};
    Packet *packet0{}, *packet1{}, *packet2{}, *packet3{}, *packet4{}, *packet5{};

    void SetUp() override {
        pQueueEmpty = new Queue<Packet>();
        pQueueWith1 = new Queue<Packet>();
        pQueueWith3 = new Queue<Packet>();
        packet0 = new Packet(1, 0, 0, ip);
        packet1 = new Packet(1, 1, 0, ip);
        packet2 = new Packet(1, 2, 0, ip);
        packet3 = new Packet(1, 3, 0, ip);
        packet4 = new Packet(1, 4, 0, ip);
        packet5 = new Packet(1, 5, 0, ip);
        pQueueWith1->enqueue(packet0);
        pQueueWith3->enqueue(packet1);
        pQueueWith3->enqueue(packet2);
        pQueueWith3->enqueue(packet3);
    }

    void TearDown() override {
        delete pQueueEmpty;
        delete pQueueWith1;
        delete pQueueWith3;
        pQueueEmpty = nullptr;
        pQueueWith1 = nullptr;
        pQueueWith3 = nullptr;
        packet0 = nullptr;
        packet1 = nullptr;
        packet2 = nullptr;
        packet3 = nullptr;
        packet4 = nullptr;
        packet5 = nullptr;
    }
};

TEST_F(QueueTest, IsEmptyInitially) {
    EXPECT_TRUE(pQueueEmpty->isEmpty());
}

// Enqueue Tests
TEST_F(QueueTest, NotEmptyAfterEnqueue) {
    pQueueEmpty->enqueue(packet4);
    EXPECT_FALSE(pQueueEmpty->isEmpty());
    EXPECT_EQ(pQueueEmpty->getNodeCount(),1);
}

TEST_F(QueueTest, EnqueueMultipleElements) {
    pQueueWith1->enqueue(packet4);
    pQueueWith1->enqueue(packet5);
    EXPECT_EQ(pQueueWith1->getDataAtNode(1), packet4);
    EXPECT_EQ(pQueueWith1->getDataAtNode(2), packet5);
    EXPECT_EQ(pQueueWith1->getNodeCount(),3);
}

// Dequeue Tests
TEST_F(QueueTest, DequeueEmptyQueue) {
    pQueueEmpty->dequeue();
    EXPECT_TRUE(pQueueEmpty->isEmpty());
    EXPECT_EQ(pQueueEmpty->getNodeCount(),0);
}

TEST_F(QueueTest, IsEmptyAfterDequeueLastElement) {
    pQueueWith1->dequeue();
    EXPECT_TRUE(pQueueWith1->isEmpty());
    EXPECT_EQ(pQueueEmpty->getNodeCount(),0);
}

TEST_F(QueueTest, DequeueMultipleElements) {
    pQueueWith3->dequeue();
    pQueueWith3->dequeue();
    EXPECT_EQ(pQueueWith3->getHeadData(), packet3);
    EXPECT_EQ(pQueueWith3->getNodeCount(),1);
}