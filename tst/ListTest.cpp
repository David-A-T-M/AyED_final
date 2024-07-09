//
// Created by David on 06/07/2024.
//
#include "gtest/gtest.h"
#include "../include/List.hpp"
/*
class ListTest : public ::testing::Test {
protected:
    int data[3] = {1, 2, 3};
    List<int> emptyList;
    List<int> listWith3;

    void SetUp() override {
        emptyList = List<int>();
        listWith3 = List<int>();
        for (int & i : data) {
            listWith3.pushBack(i);
        }
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

// Constructor Tests
TEST_F(ListTest, ListConstructorCreatesEmptyList) {
    List<int> aNewList;

    ASSERT_EQ(aNewList.getHeadData(), nullptr);
    ASSERT_EQ(aNewList.getTailData(), nullptr);
    ASSERT_EQ(aNewList.getNodeCount(), 0);
}

// PushFront Tests
TEST_F(ListTest, PushFrontToEmptyListSetsHeadAndTailAndCount) {
    emptyList.pushFront(data[0]);

    ASSERT_EQ(*emptyList.getHeadData(), data[0]);
    ASSERT_EQ(*emptyList.getTailData(), data[0]);
    ASSERT_EQ(emptyList.getNodeCount(), 1);
}

TEST_F(ListTest, PushFrontToNonEmptyListOnlyChangesHeadAndCount) {
    emptyList.pushFront(data[0]);
    emptyList.pushFront(data[1]);

    ASSERT_EQ(*emptyList.getHeadData(), data[1]);
    ASSERT_EQ(*emptyList.getTailData(), data[0]);
    ASSERT_EQ(emptyList.getNodeCount(), 2);
}

TEST_F(ListTest, PushFrontMaintainsListOrder) {
    emptyList.pushFront(data[0]);
    emptyList.pushFront(data[1]);
    emptyList.pushFront(data[2]);

    ASSERT_EQ(*emptyList.getDataAtNode(0), data[2]);
    ASSERT_EQ(*emptyList.getDataAtNode(1), data[1]);
    ASSERT_EQ(*emptyList.getDataAtNode(2), data[0]);
}

// PushBack Tests
TEST_F(ListTest, PushBackToEmptyListSetsHeadAndTailAndCount) {
    emptyList.pushBack(data[0]);

    ASSERT_EQ(*emptyList.getHeadData(), data[0]);
    ASSERT_EQ(*emptyList.getTailData(), data[0]);
    ASSERT_EQ(emptyList.getNodeCount(), 1);
}

TEST_F(ListTest, PushBackToNonEmptyListOnlyChangesTailAndCount) {
    emptyList.pushFront(data[0]);
    emptyList.pushBack(data[1]);

    ASSERT_EQ(*emptyList.getHeadData(), data[0]);
    ASSERT_EQ(*emptyList.getTailData(), data[1]);
    ASSERT_EQ(emptyList.getNodeCount(), 2);
}

TEST_F(ListTest, PushBackMaintainsListOrder) {
    emptyList.pushBack(data[0]);
    emptyList.pushBack(data[1]);
    emptyList.pushBack(data[2]);

    ASSERT_EQ(*emptyList.getDataAtNode(0), data[0]);
    ASSERT_EQ(*emptyList.getDataAtNode(1), data[1]);
    ASSERT_EQ(*emptyList.getDataAtNode(2), data[2]);
}

// PushAt Tests
TEST_F(ListTest, PushAtInvalidPositionDoesNotAlterList) {
    int inv1 = -1;
    int inv2 = 5;
    int newData = 2;
    listWith3.pushAt(newData, inv1);
    listWith3.pushAt(newData, inv2);

    ASSERT_EQ(listWith3.getNodeCount(), 3);
    ASSERT_EQ(*listWith3.getHeadData(), 1);
    ASSERT_EQ(*listWith3.getTailData(), 3);
}

TEST_F(ListTest, PushAt0){
    int newData = 0;
    listWith3.pushAt(newData, 0);

    ASSERT_EQ(*listWith3.getDataAtNode(0), newData);
    ASSERT_EQ(*listWith3.getDataAtNode(1), 1);
    ASSERT_EQ(*listWith3.getDataAtNode(2), 2);
    ASSERT_EQ(*listWith3.getDataAtNode(3), 3);
    ASSERT_EQ(listWith3.getNodeCount(), 4);
}

TEST_F(ListTest, PushAtTail){
    int newData = 0;
    listWith3.pushAt(newData, 3);

    ASSERT_EQ(*listWith3.getDataAtNode(0), 1);
    ASSERT_EQ(*listWith3.getDataAtNode(1), 2);
    ASSERT_EQ(*listWith3.getDataAtNode(2), 3);
    ASSERT_EQ(*listWith3.getDataAtNode(3), newData);
    ASSERT_EQ(listWith3.getNodeCount(), 4);
}

TEST_F(ListTest, PushAtMiddle){
    int newData = 0;
    listWith3.pushAt(newData, 2);

    ASSERT_EQ(*listWith3.getDataAtNode(0), 1);
    ASSERT_EQ(*listWith3.getDataAtNode(1), 2);
    ASSERT_EQ(*listWith3.getDataAtNode(2), newData);
    ASSERT_EQ(*listWith3.getDataAtNode(3), 3);
    ASSERT_EQ(listWith3.getNodeCount(), 4);
}

// PopFront Tests
TEST_F(ListTest, PopFrontEmptyListDoesNothing) {
    emptyList.popFront();

    ASSERT_EQ(emptyList.getNodeCount(), 0);
    ASSERT_EQ(emptyList.getHeadData(), nullptr);
    ASSERT_EQ(emptyList.getTailData(), nullptr);
}

TEST_F(ListTest, PopFrontListWith1NodeSetsHeadAndTailToNull) {
    emptyList.pushBack(data[0]);
    emptyList.popFront();

    ASSERT_EQ(emptyList.getNodeCount(), 0);
    ASSERT_EQ(emptyList.getHeadData(), nullptr);
    ASSERT_EQ(emptyList.getTailData(), nullptr);
}

TEST_F(ListTest, PopFrontNonEmptyListRemovesHeadAndDecreasesCount) {
    listWith3.popFront();

    ASSERT_EQ(listWith3.getNodeCount(), 2);
    ASSERT_EQ(*listWith3.getHeadData(), 2);
    ASSERT_EQ(*listWith3.getTailData(), 3);
}

// PopBack Tests
TEST_F(ListTest, PopBackEmptyListDoesNothing) {
    emptyList.popBack();

    ASSERT_EQ(emptyList.getNodeCount(), 0);
    ASSERT_EQ(emptyList.getHeadData(), nullptr);
    ASSERT_EQ(emptyList.getTailData(), nullptr);
}

TEST_F(ListTest, PopBackListWith1NodeSetsHeadAndTailToNull) {
    emptyList.pushBack(data[0]);
    emptyList.popBack();

    ASSERT_EQ(emptyList.getNodeCount(), 0);
    ASSERT_EQ(emptyList.getHeadData(), nullptr);
    ASSERT_EQ(emptyList.getTailData(), nullptr);
}

TEST_F(ListTest, PopBackNonEmptyListRemovesTailAndDecreasesCount) {
    listWith3.popBack();

    ASSERT_EQ(listWith3.getNodeCount(), 2);
    ASSERT_EQ(*listWith3.getHeadData(), 1);
    ASSERT_EQ(*listWith3.getTailData(), 2);
}

// PopAt Tests
TEST_F(ListTest, PopAtInvalidPositionDoesNotAlterList) {
    int inv1 = -1;
    int inv2 = 5;
    listWith3.popAt(inv1);
    listWith3.popAt(inv2);

    ASSERT_EQ(listWith3.getNodeCount(), 3);
    ASSERT_EQ(*listWith3.getHeadData(), 1);
    ASSERT_EQ(*listWith3.getTailData(), 3);
}

TEST_F(ListTest, PopAt0){
    listWith3.popAt(0);

    ASSERT_EQ(*listWith3.getDataAtNode(0), 2);
    ASSERT_EQ(*listWith3.getDataAtNode(1), 3);
    ASSERT_EQ(listWith3.getNodeCount(), 2);
}

TEST_F(ListTest, PopAtTail){
    listWith3.popAt(2);

    ASSERT_EQ(*listWith3.getDataAtNode(0), 1);
    ASSERT_EQ(*listWith3.getDataAtNode(1), 2);
    ASSERT_EQ(listWith3.getNodeCount(), 2);
}

TEST_F(ListTest, PopAtMiddle){
    listWith3.popAt(1);

    ASSERT_EQ(*listWith3.getDataAtNode(0), 1);
    ASSERT_EQ(*listWith3.getDataAtNode(1), 3);
    ASSERT_EQ(listWith3.getNodeCount(), 2);
}

// SwapNodesAt Tests
TEST_F(ListTest, SwapNodesAtInvalidPositionsDoesNotAlterList) {
    int inv1 = -1;
    int inv2 = 5;
    listWith3.swapNodesAt(inv1, inv2);

    ASSERT_EQ(*listWith3.getDataAtNode(0), 1);
    ASSERT_EQ(*listWith3.getDataAtNode(1), 2);
    ASSERT_EQ(*listWith3.getDataAtNode(2), 3);
}

TEST_F(ListTest, SwapNodesAtSamePositionDoesNotAlterList) {
    listWith3.swapNodesAt(0, 0);

    ASSERT_EQ(*listWith3.getDataAtNode(0), 1);
    ASSERT_EQ(*listWith3.getDataAtNode(1), 2);
    ASSERT_EQ(*listWith3.getDataAtNode(2), 3);
}

TEST_F(ListTest, SwapNodesAt0And1){
    listWith3.swapNodesAt(0, 1);

    ASSERT_EQ(*listWith3.getDataAtNode(0), 2);
    ASSERT_EQ(*listWith3.getDataAtNode(1), 1);
    ASSERT_EQ(*listWith3.getDataAtNode(2), 3);
}

// getHeadData Tests
TEST_F(ListTest, GetHeadDataEmptyListReturnsNullptr) {
    ASSERT_EQ(emptyList.getHeadData(), nullptr);
}

TEST_F(ListTest, GetHeadDataNonEmptyListReturnsHeadData) {
    ASSERT_EQ(*listWith3.getHeadData(), data[0]);
}

// getTailData Tests
TEST_F(ListTest, GetTailDataEmptyListReturnsNullptr) {
    ASSERT_EQ(emptyList.getTailData(), nullptr);
}

TEST_F(ListTest, GetTailDataNonEmptyListReturnsTailData) {
    ASSERT_EQ(*listWith3.getTailData(), data[2]);
}

// getDataAtNode Tests
TEST_F(ListTest, GetDataAtNodeInvalidPositionReturnsNullptr) {
    ASSERT_EQ(emptyList.getDataAtNode(-1), nullptr);
    ASSERT_EQ(emptyList.getDataAtNode(0), nullptr);
    ASSERT_EQ(emptyList.getDataAtNode(1), nullptr);
}

TEST_F(ListTest, GetDataAtNodeValidPositionReturnsData) {
    ASSERT_EQ(*listWith3.getDataAtNode(0), data[0]);
    ASSERT_EQ(*listWith3.getDataAtNode(1), data[1]);
    ASSERT_EQ(*listWith3.getDataAtNode(2), data[2]);
}

// getPos Tests
TEST_F(ListTest, GetPosEmptyListReturnsNegative1) {
    int data = 1;
    ASSERT_EQ(emptyList.getPos(data), -1);
}

TEST_F(ListTest, GetPosNonEmptyListReturnsPosition) {
    int data = 2;
    ASSERT_EQ(listWith3.getPos(data), 1);
}

// getNodeCount Tests
TEST_F(ListTest, GetNodeCountEmptyListReturns0) {
    ASSERT_EQ(emptyList.getNodeCount(), 0);
}

TEST_F(ListTest, GetNodeCountNonEmptyListReturnsCount) {
    ASSERT_EQ(listWith3.getNodeCount(), 3);
}

// isEmpty Tests
TEST_F(ListTest, IsEmptyEmptyListReturnsTrue) {
    ASSERT_TRUE(emptyList.isEmpty());
}

TEST_F(ListTest, IsEmptyNonEmptyListReturnsFalse) {
    ASSERT_FALSE(listWith3.isEmpty());
}

// Contains Tests
TEST_F(ListTest, ContainsEmptyListReturnsFalse) {
    int data = 1;
    ASSERT_FALSE(emptyList.contains(data));
}

TEST_F(ListTest, ContainsNonEmptyListReturnsTrue) {
    int data = 2;
    ASSERT_TRUE(listWith3.contains(data));
}

TEST_F(ListTest, ContainsNonEmptyListReturnsFalse) {
    int data = 4;
    ASSERT_FALSE(listWith3.contains(data));
}

// Print Tests
TEST_F(ListTest, PrintEmptyListPrintsNothing) {
    testing::internal::CaptureStdout();
    emptyList.printList();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "Fin de lista\n");
}

TEST_F(ListTest, PrintNonEmptyListPrintsData) {
    testing::internal::CaptureStdout();
    listWith3.printList();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "1\n2\n3\nFin de lista\n");
}*/