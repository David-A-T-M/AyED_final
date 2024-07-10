//
// Created by David on 06/07/2024.
//
#include "gtest/gtest.h"
#include "../include/Page.hpp"

class PageTest : public ::testing::Test {
protected:
    IPAddress originIP{170, 0b11001100};
    IPAddress destinationIP{160, 0b11001101};
    Page *page = new Page(1, 5, originIP, destinationIP);
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Constructor and getter tests
TEST_F(PageTest, PageCreation) {
    EXPECT_EQ(page->getPageID(), 1);
    EXPECT_EQ(page->getPageLength(), 5);
    EXPECT_EQ(page->getOriginIP(), originIP);
    EXPECT_EQ(page->getDestinationIP(), destinationIP);
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