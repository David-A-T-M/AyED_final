#include "gtest/gtest.h"
#include "Page.hpp"

class PageTest : public ::testing::Test {
protected:
    IPAddress originIP{170, 0b11001100};
    IPAddress destinationIP{160, 0b11001101};
    Page *page0{};
    Packet *packet0 = new Packet(1, 0, 3, 0, destinationIP, originIP);
    Packet *packet1 = new Packet(1, 1, 3, 0, destinationIP, originIP);
    Packet *packet2 = new Packet(1, 2, 3, 0, destinationIP, originIP);
    List<Node<Packet>> *list{};
    void SetUp() override {
        list = new List<Node<Packet>>();
        list->pushBack(packet0);
        list->pushBack(packet1);
        list->pushBack(packet2);
        page0 = new Page(1, 5, originIP, destinationIP);
    }

    void TearDown() override {
        for (int i = 0; i < page0->getPageLength(); i++){
            delete page0->getDataAtNode(i);
        }
        delete page0;
    }
};

// Constructor and getter tests
TEST_F(PageTest, PageCreation) {
    EXPECT_EQ(page0->getPageID(), 1);
    EXPECT_EQ(page0->getNode(0)->getData()->getPageID(), 1);
    EXPECT_EQ(page0->getNode(0)->getData()->getPagePosition(), 0);
    EXPECT_EQ(page0->getNode(1)->getData()->getPageID(), 1);
    EXPECT_EQ(page0->getNode(1)->getData()->getPagePosition(), 1);
    EXPECT_EQ(page0->getNode(2)->getData()->getPageID(), 1);
    EXPECT_EQ(page0->getNode(2)->getData()->getPagePosition(), 2);
    EXPECT_EQ(page0->getPageLength(), 5);
    EXPECT_EQ(page0->getOriginIP(), originIP);
    EXPECT_EQ(page0->getDestinationIP(), destinationIP);
}

// Constructor with list test
TEST_F(PageTest, PageFromList) {
    Page *page = new Page(list);
    EXPECT_EQ(page->getPageID(), 1);
    EXPECT_EQ(page->getPageLength(), 3);
    EXPECT_EQ(page->getOriginIP(), originIP);
    EXPECT_EQ(page->getDestinationIP(), destinationIP);
}

// Print test
TEST_F(PageTest, Print) {
    testing::internal::CaptureStdout();
    page0->print();
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