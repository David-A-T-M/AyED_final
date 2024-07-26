//
// Created by David on 08/07/2024.
//
#include "gtest/gtest.h"
#include "../include/Packet.hpp"

class PacketTest : public ::testing::Test {
protected:
    IPAddress ip1{170, 0b11001100};
    IPAddress ip2{0b11001100, 170};
    Packet packet1{1, 2, 5, 3, ip1, ip2};
    Packet packet2{1, 2, 5, 3, ip1, ip2};
    Packet packet3{1, 3, 5, 3, ip1, ip2};
    Packet packet4{2, 2, 5, 3, ip1, ip2};

    void SetUp() override {
    }
};

// Constructor and getter tests
TEST_F(PacketTest, PacketCreation) {
    EXPECT_EQ(packet1.getPageID(), 1);
    EXPECT_EQ(packet1.getPagePosition(), 2);
    EXPECT_EQ(packet1.getPageLength(), 5);
    EXPECT_EQ(packet1.getRouterPriority(), 3);
    EXPECT_EQ(packet1.getDestinationIP(), ip1);
    EXPECT_EQ(packet1.getOriginIP(), ip2);
}

// Setters tests
TEST_F(PacketTest, Setters) {
    packet1.setRouterPriority(1);
    EXPECT_EQ(packet1.getRouterPriority(), 1);
}

// toString test
TEST_F(PacketTest, ToString) {
    EXPECT_EQ(packet1.toString(), "170000000001-2");
}

// Equal operator test
TEST_F(PacketTest, EqualOperator) {
    EXPECT_TRUE(packet1 == packet2);
    EXPECT_FALSE(packet1 == packet3);
    EXPECT_FALSE(packet1 == packet4);
}