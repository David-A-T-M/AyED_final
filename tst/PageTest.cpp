//
// Created by David on 06/07/2024.
//
#include "gtest/gtest.h"
#include "../include/Page.hpp"

class PageTest : public ::testing::Test {
protected:
    IPAddress terminal1IP = IPAddress(170, 0b11001100);
    IPAddress terminal2IP = IPAddress(180, 0b11001101);
    Page* page{};

    void SetUp() override {
        page = new Page(1, 5, terminal1IP, terminal2IP);
    }

    void TearDown() override {
        delete page;
    }
};

// Constructor and getter tests
TEST_F(PageTest, PageCreation) {
    EXPECT_EQ(page->getPageID(), 1);
    EXPECT_EQ(page->getPageLength(), 5);
    EXPECT_EQ(page->getOriginIP(), terminal1IP);
    EXPECT_EQ(page->getDestinationIP(), terminal2IP);
}

// Print test
TEST_F(PageTest, Print) {
    testing::internal::CaptureStdout();
    page->print();
    std::string output = testing::internal::GetCapturedStdout();
    std::string expectedOutput = "Page ID: 1\n"
                                 "Packet 0\n"
                                 "Packet 1\n"
                                 "Packet 2\n"
                                 "Packet 3\n"
                                 "Packet 4\n"
                                 "Page length: 5\n\n";
    EXPECT_EQ(output, expectedOutput);
}