//
// Created by David on 07/07/2024.
//
#include <gtest/gtest.h>
#include "Terminal.hpp"
#include "Router.hpp"

class TerminalTest : public ::testing::Test {
protected:
    IPAddress *destIP{}, *origIP{};
    Terminal *terminal{};
    Page *page0{};
    Router *router{};
    int getIDForPage(Terminal *ter) {
        return ter->idForPage;
    }
    Router *getConnectedRouter(Terminal *ter) {
        return ter->connectedRouter;
    }
    void SetUp() override {
        destIP = new IPAddress(120, 170);
        origIP = new IPAddress(172, 168);
        router = new Router();
        terminal = new Terminal(*origIP, router);
        page0 = new Page(1, 100, *origIP, *destIP);
    }

    void TearDown() override {
        delete destIP;
        delete origIP;
        delete router;
        delete terminal;
        destIP = nullptr;
        origIP = nullptr;
        router = nullptr;
        terminal = nullptr;
        page0 = nullptr;
    }
};

// Constructor and getter test
TEST_F(TerminalTest, Constructor) {
    EXPECT_EQ(terminal->getTerminalIp(), *origIP);
    EXPECT_EQ(terminal->getReceivedPages(), 0);
    EXPECT_EQ(terminal->getSentPages(), 0);
    EXPECT_EQ(getIDForPage(terminal), 168000);
}

// SendPage test
TEST_F(TerminalTest, SendPage) {
    terminal->sendPage(10, *destIP);
    EXPECT_EQ(terminal->getSentPages(), 1);
}

// ReceivePage test
TEST_F(TerminalTest, ReceivePage) {
    terminal->receivePage(page0);
    EXPECT_EQ(terminal->getReceivedPages(), 1);
}

// Router field test
TEST_F(TerminalTest, RouterField) {
    EXPECT_EQ(getConnectedRouter(terminal), router);
}