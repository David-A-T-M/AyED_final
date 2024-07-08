//
// Created by David on 08/07/2024.
//
#include "gtest/gtest.h"
#include "../include/Packet.hpp"

class PacketTest : public ::testing::Test {
protected:
    IPAddress terminalIP{170, 0b11001100};
    Packet packet1{1, 2, 3, terminalIP};
    Packet packet2{1, 2, 3, terminalIP};
    Packet packet3{1, 3, 3, terminalIP};
    Packet packet4{2, 2, 3, terminalIP};
    Packet packet5{1, 2, 4, terminalIP};

    void SetUp() override {
    }
};

// Constructor and getter tests
TEST_F(PacketTest, PacketCreation) {
    EXPECT_EQ(packet1.getPageID(), 1);
    EXPECT_EQ(packet1.getPagePosition(), 2);
    EXPECT_EQ(packet1.getRouterPosition(), 3);
    EXPECT_EQ(packet1.getDestinationIP(), terminalIP);
}

// toString test
TEST_F(PacketTest, ToString) {
    EXPECT_EQ(packet1.toString(), "Packet 2");
}

// Equal operator test
TEST_F(PacketTest, EqualOperator) {
    EXPECT_TRUE(packet1 == packet2);
    EXPECT_FALSE(packet1 == packet3);
    EXPECT_FALSE(packet1 == packet4);
    EXPECT_FALSE(packet1 == packet5);
}