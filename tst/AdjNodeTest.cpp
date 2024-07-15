//
// Created by David on 11/07/2024.
//
#include <gtest/gtest.h>
#include "AdjNode.hpp"
#include "Packet.hpp"

class AdjacencyNodeTest : public ::testing::Test {
protected:
    IPAddress terminalIP{170, 0b11001100};
    Packet *packet0{}, *packet1{}, *packet2{};
    AdjNode<Packet> *node0{}, *node1{}, *node2{}, *node3{};
    void SetUp() override {
        packet0 = new Packet(1, 1, 0, terminalIP);
        packet1 = new Packet(1, 2, 0, terminalIP);
        node0 = new AdjNode<Packet>(packet0);
        node1 = new AdjNode<Packet>(packet0, 10);
        node2 = new AdjNode<Packet>(packet0, node1);
        node3 = new AdjNode<Packet>(packet0, node2, 20);
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
        packet0 = nullptr;
        packet1 = nullptr;
    }
};


// Constructor and getter tests
TEST_F(AdjacencyNodeTest, DataConstructor) {
    EXPECT_EQ(node0->getData(), packet0);
    EXPECT_EQ(node0->getVal(), 0);
}

TEST_F(AdjacencyNodeTest, DataValConstructor) {
    EXPECT_EQ(node1->getData(), packet0);
    EXPECT_EQ(node1->getVal(), 10);
}

TEST_F(AdjacencyNodeTest, DataNextConstructor) {
    EXPECT_EQ(node2->getData(), packet0);
    EXPECT_EQ(node2->getVal(), 0);
    EXPECT_EQ(node2->getNext(), node1);
}

TEST_F(AdjacencyNodeTest, DataNextValConstructor) {
    EXPECT_EQ(node3->getData(), packet0);
    EXPECT_EQ(node3->getVal(), 20);
    EXPECT_EQ(node3->getNext(), node2);
}

// Setter tests
TEST_F(AdjacencyNodeTest, SetWeight) {
    node3->setVal(5);
    node3->setData(packet1);
    node3->setNext(node0);
    EXPECT_EQ(node3->getVal(), 5);
    EXPECT_EQ(node3->getData(), packet1);
    EXPECT_EQ(node3->getNext(), node0);
}