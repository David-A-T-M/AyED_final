#include "gtest/gtest.h"
#include "IPAddress.hpp"

class IPAddressTest : public ::testing::Test {
protected:
    IPAddress modem1{170};
    IPAddress modem2{0b10101010};
    IPAddress modem3{25};
    IPAddress terminal1{170, 0b11001100};
    IPAddress terminal2{0b10101010, 204};
    IPAddress terminal3{0b10101010, 108};
    void SetUp() override {
    }
};

TEST_F(IPAddressTest, CreateModemIPAddress) {
    IPAddress ip{0b10101010};
    EXPECT_TRUE(ip.isRouter());
}

TEST_F(IPAddressTest, CreateTerminalIPAddress) {
    IPAddress ip{0b10101010, 0b11001100};
    EXPECT_FALSE(ip.isRouter());
}

TEST_F(IPAddressTest, ModemIPToString) {
    EXPECT_EQ(modem1.toString(), "Router IP: 10101010");
}

TEST_F(IPAddressTest, TerminalIPToString) {
    EXPECT_EQ(terminal1.toString(), "Terminal IP: 10101010.11001100");
}

TEST_F(IPAddressTest, GetModemIP) {
    EXPECT_EQ(modem1.getRouterIP(), 0b10101010);
    EXPECT_EQ(terminal1.getRouterIP(), 0b10101010);
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