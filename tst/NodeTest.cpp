//
// Created by David on 05/07/2024.
//
#include "gtest/gtest.h"
#include "../include/Node.hpp"
#include "Packet.hpp"

class NodeTest : public ::testing::Test {
protected:
    IPAddress terminalIP{170, 0b11001100};
    Packet* packet0{};
    Packet* packet1{};
    Packet* packet2{};
    Packet* packet3{};
    Packet* packet4{};
    Node<Packet>* node1{};
    Node<Packet>* node2{};
    Node<Packet>* node3{};
    Node<Packet>* node4{};
    void SetUp() override {
        packet1 = new Packet(1, 1, 0, terminalIP);
        packet2 = new Packet(1, 2, 0, terminalIP);
        packet3 = new Packet(1, 3, 0, terminalIP);
        packet4 = new Packet(1, 4, 0, terminalIP);
        node2 = new Node<Packet>(packet2);
        node1 = new Node<Packet>(packet1,node2);
        node3 = new Node<Packet>(packet3);
        node4 = new Node<Packet>(packet1);
    }
    void TearDown() override {
        delete node1;
        delete node2;
        delete node3;
        node1 = nullptr;
        node2 = nullptr;
        node3 = nullptr;
        packet1 = nullptr;
        packet2 = nullptr;
        packet3 = nullptr;
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
    ASSERT_EQ(node1->getData(), packet1);
    ASSERT_NE(node1->getNext(), nullptr);
    ASSERT_EQ(node1->getNext(), node2);
}

// Setter Tests
TEST_F(NodeTest, SetData) {
    EXPECT_EQ(node1->getData(), packet1);
    node1->setData(packet4);
    EXPECT_EQ(node1->getData(), packet4);
}

TEST_F(NodeTest, SetNext) {
    EXPECT_EQ(node1->getNext(), node2);
    node1->setNext(node3);
    EXPECT_EQ(node1->getNext(), node3);
}

// HasNext Test
TEST_F(NodeTest, HasNext) {
    EXPECT_FALSE(node2->hasNext());
    EXPECT_TRUE(node1->hasNext());
}

// Operator == Tests
TEST_F(NodeTest, OperatorEqual) {
    EXPECT_TRUE(*node1 == *node4);
    EXPECT_FALSE(*node1 == *node2);
}

// toString Test
TEST_F(NodeTest, ToString) {
    EXPECT_EQ(node1->toString(), "Packet 1");
}