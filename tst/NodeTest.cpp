//
// Created by David on 05/07/2024.
//
#include "gtest/gtest.h"
#include "../include/Node.hpp"
#include "Packet.hpp"

class NodeTest : public ::testing::Test {
protected:
    IPAddress terminalIP = IPAddress(170, 0b11001100);

    void SetUp() override {
    }
};

// Constructor Tests
TEST(NodeTest, DefaultConstructor) {
    Node<Packet> node();
    EXPECT_EQ(node.getNext(), nullptr);
    EXPECT_EQ(*node.getData(), 0);
}

TEST(NodeTest, DataConstructor) {
    Node<int> node(5);
    EXPECT_EQ(*node.getData(), 5);
    EXPECT_EQ(node.getNext(), nullptr);
}

TEST(NodeTest, DataNextConstructor) {
    Node<int> nextNode(10);
    Node<int> node(5, &nextNode);
    EXPECT_EQ(*node.getData(), 5);
    ASSERT_NE(node.getNext(), nullptr);
    EXPECT_EQ(*node.getNext()->getData(), 10);
}

// Setter Tests
TEST(NodeTest, SetData) {
    Node<int> node;
    int newData = 20;
    node.setData(newData);
    EXPECT_EQ(*node.getData(), 20);
}

TEST(NodeTest, SetNext) {
    Node<int> node1;
    Node<int> node2;
    node1.setNext(&node2);
    EXPECT_EQ(node1.getNext(), &node2);
}

// Getter Tests
TEST(NodeTest, GetData) {
    Node<int> node(5);
    EXPECT_EQ(*node.getData(), 5);
}

TEST(NodeTest, GetNext) {
    Node<int> node1;
    Node<int> node2;
    node1.setNext(&node2);
    EXPECT_EQ(node1.getNext(), &node2);
}

// HasNext Test
TEST(NodeTest, HasNext) {
    Node<int> node1;
    Node<int> node2;
    EXPECT_FALSE(node1.hasNext());
    node1.setNext(&node2);
    EXPECT_TRUE(node1.hasNext());
}

// Operator == Tests
TEST(NodeTest, OperatorEqual) {
    Node<int> node(5);
    int someInt = 5;
    EXPECT_TRUE(node == someInt);
    someInt = 10;
    EXPECT_FALSE(node == someInt);
}

// toString Test
TEST(NodeTest, ToString) {
    Node<int> node(5);
    EXPECT_EQ(node.toString(), "Node: 5");
}