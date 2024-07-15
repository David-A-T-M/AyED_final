//
// Created by David on 11/07/2024.
//
#include <gtest/gtest.h>
#include "AdjNode.hpp"
#include "Router.hpp"

class AdjacencyNodeTest : public ::testing::Test {
protected:
    Router *router0{}, *router1{};
    AdjNode *node0{}, *node1{};
    void SetUp() override {
        router0 = new Router();
        router1 = new Router();
        node0 = new AdjNode(router0);
        node1 = new AdjNode(router1, 10);
    }
    void TearDown() override {
        delete node0;
        delete node1;
        node0 = nullptr;
        node1 = nullptr;
        delete router0;
        delete router1;
        router0 = nullptr;
        router1 = nullptr;
    }
};


// Constructor and getter tests
TEST_F(AdjacencyNodeTest, Constructor) {
    EXPECT_EQ(node0->getData(), router0);
    EXPECT_EQ(node1->getData(), router1);
    EXPECT_EQ(node0->getWeight(), 0);
    EXPECT_EQ(node1->getWeight(), 10);
}

// Setter tests
TEST_F(AdjacencyNodeTest, SetWeight) {
    node0->setWeight(5);
    node1->setWeight(15);
    EXPECT_EQ(node0->getWeight(), 5);
    EXPECT_EQ(node1->getWeight(), 15);
}