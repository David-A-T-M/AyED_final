//
// Created by David on 05/07/2024.
//
#include "gtest/gtest.h"
#include "../include/Node.hpp"
#include "Packet.hpp"

class NodeTest : public ::testing::Test {
protected:
    IPAddress ip1{170, 0b11001100};
    IPAddress ip2{0b11001100, 170};
    Packet *packet0{}, *packet1{}, *packet2{};
    Node<Packet> *node0{}, *node1{}, *node2{}, *node3{};
    void SetUp() override {
        packet0 = new Packet(1, 1, 5, 0, ip1, ip2);
        packet1 = new Packet(1, 2, 5, 0, ip1, ip2);
        packet2 = new Packet(1, 3, 5, 0, ip1, ip2);
        node1 = new Node<Packet>(packet1);
        node0 = new Node<Packet>(packet0, node1);
        node2 = new Node<Packet>(packet2);
        node3 = new Node<Packet>(packet0);
    }
    void TearDown() override {
        delete node0;
        delete node1;
        delete node2;
        delete node3;
        node0 = nullptr;
        node1 = nullptr;
        node2 = nullptr;
        node3 = nullptr;
        delete packet0;
        delete packet1;
        delete packet2;
        packet0 = nullptr;
        packet1 = nullptr;
        packet2 = nullptr;
    }
};

// Constructor and getter tests
TEST_F(NodeTest, DefaultConstructor) {
    Node<Packet> node{};
    EXPECT_EQ(node.getData(), nullptr);
    EXPECT_EQ(node.getNext(), nullptr);
}

TEST_F(NodeTest, DataConstructor) {
    Node<Packet> node{packet0};
    EXPECT_EQ(node.getData(), packet0);
    EXPECT_EQ(node.getNext(), nullptr);
}

TEST_F(NodeTest, DataNextConstructor) {
    ASSERT_EQ(node0->getData(), packet0);
    ASSERT_NE(node0->getNext(), nullptr);
    ASSERT_EQ(node0->getNext(), node1);
}

// Setter Tests
TEST_F(NodeTest, SetData) {
    EXPECT_EQ(node0->getData(), packet0);
    node0->setData(packet1);
    EXPECT_EQ(node0->getData(), packet1);
}

TEST_F(NodeTest, SetNext) {
    EXPECT_EQ(node0->getNext(), node1);
    node0->setNext(node2);
    EXPECT_EQ(node0->getNext(), node2);
}

// HasNext Test
TEST_F(NodeTest, HasNext) {
    EXPECT_FALSE(node1->hasNext());
    EXPECT_TRUE(node0->hasNext());
}

// Operator == Tests
TEST_F(NodeTest, OperatorEqual) {
    EXPECT_TRUE(*node0 == *node3);
    EXPECT_FALSE(*node0 == *node1);
}

// toString Test
TEST_F(NodeTest, ToString) {
    EXPECT_EQ(node0->toString(), "170000000001-1");
}