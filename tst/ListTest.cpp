//
// Created by David on 06/07/2024.
//
#include "gtest/gtest.h"
#include "../include/List.hpp"
#include "Packet.hpp"

class ListTest : public ::testing::Test {
protected:
    IPAddress ip{170, 0b11001100};
    List<Packet> *pEmptyList{}, *pListWith1{}, *pListWith3{};
    Packet *packet0{}, *packet1{}, *packet2{}, *packet3{}, *packet4{};
    //Node<Packet> *node1{}, *node2{}, *node3{};

    void SetUp() override {
        pEmptyList = new List<Packet>();
        pListWith1 = new List<Packet>();
        pListWith3 = new List<Packet>();
        packet0 = new Packet(1, 0, 0, ip);
        packet1 = new Packet(1, 1, 0, ip);
        packet2 = new Packet(1, 2, 0, ip);
        packet3 = new Packet(1, 3, 0, ip);
        packet4 = new Packet(1, 4, 0, ip);
        pListWith1->pushBack(packet0);
        pListWith3->pushBack(packet1);
        pListWith3->pushBack(packet2);
        pListWith3->pushBack(packet3);
    }

    void TearDown() override {
        delete pEmptyList;
        delete pListWith1;
        delete pListWith3;
        pEmptyList = nullptr;
        pListWith1 = nullptr;
        pListWith3 = nullptr;
        packet0 = nullptr;
        packet1 = nullptr;
        packet2 = nullptr;
        packet3 = nullptr;
        packet4 = nullptr;
    }
};

// Constructor And Getters Tests
TEST_F(ListTest, ListConstructorCreatesEmptyList) {
    List<Packet> aNewList{};
    ASSERT_EQ(aNewList.getHeadData(), nullptr);
    ASSERT_EQ(aNewList.getTailData(), nullptr);
    ASSERT_EQ(aNewList.getNodeCount(), 0);
}

// PushFront Tests
TEST_F(ListTest, PushFrontToEmptyListSetsHeadAndTailAndCount) {
    pEmptyList->pushFront(packet4);
    ASSERT_EQ(pEmptyList->getHeadData(), packet4);
    ASSERT_EQ(pEmptyList->getTailData(), packet4);
    ASSERT_EQ(pEmptyList->getNodeCount(), 1);
}

TEST_F(ListTest, PushFrontToNonEmptyListOnlyChangesHeadAndCount) {
    pListWith1->pushFront(packet4);
    ASSERT_EQ(pListWith1->getHeadData(), packet4);
    ASSERT_EQ(pListWith1->getTailData(), packet0);
    ASSERT_EQ(pListWith1->getNodeCount(), 2);
}

// PushBack Tests
TEST_F(ListTest, PushBackToEmptyListSetsHeadAndTailAndCount) {
    pEmptyList->pushBack(packet4);
    ASSERT_EQ(pEmptyList->getHeadData(), packet4);
    ASSERT_EQ(pEmptyList->getHeadData(), packet4);
    ASSERT_EQ(pEmptyList->getNodeCount(), 1);
}

TEST_F(ListTest, PushBackToNonEmptyListOnlyChangesTailAndCount) {
    pListWith1->pushBack(packet4);
    ASSERT_EQ(pListWith1->getHeadData(), packet0);
    ASSERT_EQ(pListWith1->getTailData(), packet4);
    ASSERT_EQ(pListWith1->getNodeCount(), 2);
}

// PushAt, getDataAt Tests
TEST_F(ListTest, PushAtInvalidPositionDoesNotAlterList) {
    pListWith3->pushAt(packet4, -1);
    ASSERT_EQ(pListWith3->getNodeCount(), 3);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getDataAtNode(0), packet1);
    ASSERT_EQ(pListWith3->getTailData(), packet3);
}

TEST_F(ListTest, PushAt0){
    pListWith3->pushAt(packet4, 0);
    ASSERT_EQ(pListWith3->getHeadData(), packet4);
    ASSERT_EQ(pListWith3->getDataAtNode(1), packet1);
    ASSERT_EQ(pListWith3->getDataAtNode(2), packet2);
    ASSERT_EQ(pListWith3->getTailData(), packet3);
    ASSERT_EQ(pListWith3->getNodeCount(), 4);
}

TEST_F(ListTest, PushAtTail){
    pListWith3->pushAt(packet4, 3);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getDataAtNode(1), packet2);
    ASSERT_EQ(pListWith3->getDataAtNode(2), packet3);
    ASSERT_EQ(pListWith3->getTailData(), packet4);
    ASSERT_EQ(pListWith3->getNodeCount(), 4);
}

TEST_F(ListTest, PushAtMiddle){
    pListWith3->pushAt(packet4, 2);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getDataAtNode(1), packet2);
    ASSERT_EQ(pListWith3->getDataAtNode(2), packet4);
    ASSERT_EQ(pListWith3->getTailData(), packet3);
    ASSERT_EQ(pListWith3->getNodeCount(), 4);
}

// PopFront Tests
TEST_F(ListTest, PopFrontEmptyListDoesNothing) {
    pEmptyList->popFront();
    ASSERT_EQ(pEmptyList->getNodeCount(), 0);
    ASSERT_EQ(pEmptyList->getHeadData(), nullptr);
    ASSERT_EQ(pEmptyList->getTailData(), nullptr);
}

TEST_F(ListTest, PopFrontListWith1NodeSetsHeadAndTailToNull) {
    pListWith1->popFront();
    ASSERT_EQ(pListWith1->getNodeCount(), 0);
    ASSERT_EQ(pListWith1->getHeadData(), nullptr);
    ASSERT_EQ(pListWith1->getTailData(), nullptr);
}

TEST_F(ListTest, PopFrontNonEmptyListRemovesHeadAndDecreasesCount) {
    pListWith3->popFront();
    ASSERT_EQ(pListWith3->getNodeCount(), 2);
    ASSERT_EQ(pListWith3->getHeadData(), packet2);
    ASSERT_EQ(pListWith3->getTailData(), packet3);
}

// PopBack Tests
TEST_F(ListTest, PopBackEmptyListDoesNothing) {
    pEmptyList->popBack();
    ASSERT_EQ(pEmptyList->getNodeCount(), 0);
    ASSERT_EQ(pEmptyList->getHeadData(), nullptr);
    ASSERT_EQ(pEmptyList->getTailData(), nullptr);
}

TEST_F(ListTest, PopBackListWith1NodeSetsHeadAndTailToNull) {
    pListWith1->popBack();
    ASSERT_EQ(pListWith1->getNodeCount(), 0);
    ASSERT_EQ(pListWith1->getHeadData(), nullptr);
    ASSERT_EQ(pListWith1->getTailData(), nullptr);
}

TEST_F(ListTest, PopBackNonEmptyListRemovesTailAndDecreasesCount) {
    pListWith3->popBack();
    ASSERT_EQ(pListWith3->getNodeCount(), 2);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getTailData(), packet2);
}

// PopAt Tests
TEST_F(ListTest, PopAtInvalidPositionDoesNotAlterList) {
    pListWith3->popAt(-1);
    ASSERT_EQ(pListWith3->getNodeCount(), 3);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getDataAtNode(1), packet2);
    ASSERT_EQ(pListWith3->getTailData(), packet3);
}

TEST_F(ListTest, PopAt0){
    pListWith3->popAt(0);
    ASSERT_EQ(pListWith3->getHeadData(), packet2);
    ASSERT_EQ(pListWith3->getTailData(), packet3);
    ASSERT_EQ(pListWith3->getNodeCount(), 2);
}

TEST_F(ListTest, PopAtTail){
    pListWith3->popAt(2);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getTailData(), packet2);
    ASSERT_EQ(pListWith3->getNodeCount(), 2);
}

TEST_F(ListTest, PopAtMiddle){
    pListWith3->popAt(1);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getTailData(), packet3);
    ASSERT_EQ(pListWith3->getNodeCount(), 2);
}

// SwapNodesAt Tests
TEST_F(ListTest, SwapNodesAtInvalidPositionsDoesNotAlterList) {
    pListWith3->swapNodesAt(-1, 5);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getDataAtNode(1), packet2);
    ASSERT_EQ(pListWith3->getTailData(), packet3);
}

TEST_F(ListTest, SwapNodesAtSamePositionDoesNotAlterList) {
    pListWith3->swapNodesAt(0, 0);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getDataAtNode(1), packet2);
    ASSERT_EQ(pListWith3->getTailData(), packet3);
}

TEST_F(ListTest, SwapNodesAt0And1){
    pListWith3->swapNodesAt(0, 2);
    ASSERT_EQ(pListWith3->getHeadData(), packet3);
    ASSERT_EQ(pListWith3->getDataAtNode(1), packet2);
    ASSERT_EQ(pListWith3->getTailData(), packet1);
}

// getDataAtNode Tests
TEST_F(ListTest, GetDataAtNodeInvalidPositionReturnsNullptr) {
    ASSERT_EQ(pEmptyList->getDataAtNode(-1), nullptr);
    ASSERT_EQ(pEmptyList->getDataAtNode(0), nullptr);
    ASSERT_EQ(pEmptyList->getDataAtNode(1), nullptr);
}

// getPos Tests
TEST_F(ListTest, GetPos) {
    ASSERT_EQ(pEmptyList->getPos(packet1), -1);
    ASSERT_EQ(pListWith3->getPos(packet2), 1);
}

// isEmpty Tests
TEST_F(ListTest, IsEmpty) {
    ASSERT_TRUE(pEmptyList->isEmpty());
    ASSERT_FALSE(pListWith3->isEmpty());
}

// Contains Tests
TEST_F(ListTest, Contains) {
    ASSERT_FALSE(pEmptyList->contains(packet4));
    ASSERT_TRUE(pListWith3->contains(packet2));
    ASSERT_FALSE(pListWith3->contains(packet0));
}

// Print Tests
TEST_F(ListTest, PrintEmptyListPrintsNothing) {
    testing::internal::CaptureStdout();
    pEmptyList->printList();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Inicio de lista\nFin de lista\n");
}

TEST_F(ListTest, PrintNonEmptyListPrintsData) {
    testing::internal::CaptureStdout();
    pListWith3->printList();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Inicio de lista\nPacket 1\nPacket 2\nPacket 3\nFin de lista\n");
}