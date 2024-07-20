#include "gtest/gtest.h"
#include "Queue.hpp"
#include "Packet.hpp"
#include "Node.hpp"

class QueueTest : public ::testing::Test {
protected:
    IPAddress ip1{170, 0b10101010};
    IPAddress ip2{0b10101010, 170};
    Queue<Node<Packet>> *pQueueEmpty{}, *pQueueWith1{}, *pQueueWith3{};
    Packet *packet0{}, *packet1{}, *packet2{}, *packet3{};

    void SetUp() override {
        pQueueEmpty = new Queue<Node<Packet>>();
        pQueueWith1 = new Queue<Node<Packet>>();
        pQueueWith3 = new Queue<Node<Packet>>();
        packet0 = new Packet(1, 0, 5, 0, ip1, ip2);
        packet1 = new Packet(1, 1, 5, 0, ip1, ip2);
        packet2 = new Packet(1, 2, 5, 0, ip1, ip2);
        packet3 = new Packet(1, 3, 5, 0, ip1, ip2);
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
        delete packet0;
        delete packet1;
        delete packet2;
        delete packet3;
        packet0 = nullptr;
        packet1 = nullptr;
        packet2 = nullptr;
        packet3 = nullptr;
    }
};

TEST_F(QueueTest, IsEmptyInitially) {
    EXPECT_TRUE(pQueueEmpty->isEmpty());
    EXPECT_EQ(pQueueEmpty->getNodeCount(),0);
}

// Enqueue Tests
TEST_F(QueueTest, NotEmptyAfterEnqueue) {
    pQueueEmpty->enqueue(packet1);
    EXPECT_FALSE(pQueueEmpty->isEmpty());
    EXPECT_EQ(pQueueEmpty->getNodeCount(),1);
}

TEST_F(QueueTest, EnqueueMultipleElements) {
    pQueueWith1->enqueue(packet2);
    pQueueWith1->enqueue(packet3);
    EXPECT_EQ(pQueueWith1->getDataAtNode(1), packet2);
    EXPECT_EQ(pQueueWith1->getDataAtNode(2), packet3);
    EXPECT_EQ(pQueueWith1->getNodeCount(),3);
}

// Dequeue Tests
TEST_F(QueueTest, DequeueEmptyQueue) {
    testing::internal::CaptureStdout();
    pQueueEmpty->dequeue();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(pQueueEmpty->isEmpty());
    EXPECT_EQ(pQueueEmpty->getNodeCount(),0);
    EXPECT_EQ(output, "Can't dequeue, queue is empty\n");
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

// EnqueueList Tests
TEST_F(QueueTest, enqueueList) {
    pQueueWith1->enqueueList(pQueueWith3);
    EXPECT_EQ(pQueueWith1->getHeadData(), packet0);
    EXPECT_EQ(pQueueWith1->getDataAtNode(1), packet1);
    EXPECT_EQ(pQueueWith1->getDataAtNode(2), packet2);
    EXPECT_EQ(pQueueWith1->getTailData(), packet3);
    EXPECT_EQ(pQueueWith1->getNodeCount(),4);
}