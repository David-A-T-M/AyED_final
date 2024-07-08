#include "gtest/gtest.h"
#include "../include/IPAddress.hpp"

class IPAddressTest : public ::testing::Test {
protected:
    IPAddress modem1 = IPAddress(170);
    IPAddress modem2 = IPAddress(0b10101010);
    IPAddress modem3 = IPAddress(25);
    IPAddress terminal1 = IPAddress(170, 0b11001100);
    IPAddress terminal2 = IPAddress(0b10101010, 204);
    IPAddress terminal3 = IPAddress(0b10101010, 108);
    void SetUp() override {
    }
};

TEST_F(IPAddressTest, CreateModemIPAddress) {
    IPAddress ip(0b10101010);
    EXPECT_TRUE(ip.isModem());
}

TEST_F(IPAddressTest, CreateTerminalIPAddress) {
    IPAddress ip(0b10101010, 0b11001100);
    EXPECT_FALSE(ip.isModem());
}

TEST_F(IPAddressTest, ModemIPToString) {
    EXPECT_EQ(modem1.toString(), "Modem IP: 10101010");
}

TEST_F(IPAddressTest, TerminalIPToString) {
    EXPECT_EQ(terminal1.toString(), "Terminal IP: 10101010.11001100");
}

TEST_F(IPAddressTest, GetModemIP) {
    EXPECT_EQ(modem1.getModemIP(), 0b10101010);
    EXPECT_EQ(terminal1.getModemIP(), 0b10101010);
}

TEST_F(IPAddressTest, GetTerminalIP) {
    EXPECT_EQ(modem1.getTerminalIP(), 0);
    EXPECT_EQ(terminal1.getTerminalIP(), 0b11001100);
}

TEST_F(IPAddressTest, EqualOperator) {
    EXPECT_TRUE(modem1 == modem2);
    EXPECT_FALSE(modem1 == modem3);
    EXPECT_TRUE(terminal1 == terminal2);
    EXPECT_FALSE(terminal1 == terminal3);
}