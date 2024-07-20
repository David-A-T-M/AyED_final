#include "gtest/gtest.h"
#include "List.hpp"
#include "Packet.hpp"
#include "Node.hpp"
#include "AdjNode.hpp"

class ListTest : public ::testing::Test {
protected:
    IPAddress ip{170, 0b11001100};
    Packet *packet0{}, *packet1{}, *packet2{};
    List<Node<Packet>> *pEmptyList{}, *pListWith1{}, *pListWith3{};
    List<AdjNode<Packet>> *pAdjEmptyList{}, *pAdjListWith1{}, *pAdjListWith3{};

public:
    void SetUp() override {
        pEmptyList = new List<Node<Packet>>();
        pListWith1 = new List<Node<Packet>>();
        pListWith3 = new List<Node<Packet>>();
        pAdjEmptyList = new List<AdjNode<Packet>>();
        pAdjListWith1 = new List<AdjNode<Packet>>();
        pAdjListWith3 = new List<AdjNode<Packet>>();
        packet0 = new Packet(1, 0, 5, 0, ip, ip);
        packet1 = new Packet(1, 1, 5, 0, ip, ip);
        packet2 = new Packet(1, 2, 5, 0, ip, ip);
        pListWith1->pushBack(packet0);
        pListWith3->pushBack(packet1);
        pListWith3->pushBack(packet2);
        pListWith3->pushBack(packet2);
        pAdjListWith1->pushBack(packet0);
        pAdjListWith3->pushBack(packet1);
        pAdjListWith3->pushBack(packet2);
        pAdjListWith3->pushBack(packet2);
        auto* asd = pAdjListWith1->getNode(0);
    }

    void TearDown() override {
        delete packet0;
        delete packet1;
        delete packet2;
        delete pEmptyList;
        delete pListWith1;
        delete pListWith3;
        delete pAdjEmptyList;
        delete pAdjListWith1;
        delete pAdjListWith3;
        packet0 = nullptr;
        packet1 = nullptr;
        packet2 = nullptr;
        pEmptyList = nullptr;
        pListWith1 = nullptr;
        pListWith3 = nullptr;
        pAdjEmptyList = nullptr;
        pAdjListWith1 = nullptr;
        pAdjListWith3 = nullptr;
    }
};

// Constructor And Getters Tests
TEST_F(ListTest, DefaultConstructor) {
    ASSERT_EQ(pEmptyList->getHead(), nullptr);
    ASSERT_EQ(pEmptyList->getTail(), nullptr);
    ASSERT_EQ(pEmptyList->getHeadData(), nullptr);
    ASSERT_EQ(pEmptyList->getTailData(), nullptr);
    ASSERT_EQ(pEmptyList->getNode(0), nullptr);
    ASSERT_EQ(pEmptyList->getNodeCount(), 0);
    ASSERT_EQ(pAdjEmptyList->getHead(), nullptr);
    ASSERT_EQ(pAdjEmptyList->getTail(), nullptr);
    ASSERT_EQ(pAdjEmptyList->getNodeCount(), 0);

}

// GetHead Tests
TEST_F(ListTest, GetHeadNode) {
    Node<Packet>* head = pEmptyList->getHead();
    ASSERT_EQ(head, nullptr);
    head = pListWith1->getHead();
    ASSERT_EQ(head->getData(), packet0);
    head = pListWith3->getHead();
    ASSERT_EQ(head->getData(), packet1);
    head = nullptr;
    delete head;
}

TEST_F(ListTest, GetTailAdjNode) {
    AdjNode<Packet>* tail = pAdjEmptyList->getTail();
    ASSERT_EQ(tail, nullptr);
    tail = pAdjListWith1->getTail();
    ASSERT_EQ(tail->getData(), packet0);
    tail = pAdjListWith3->getTail();
    ASSERT_EQ(tail->getData(), packet2);
    tail = nullptr;
    delete tail;
}

// PushFront Tests
TEST_F(ListTest, PushFrontToEmptyListSetsHeadAndTailAndCount) {
    pEmptyList->pushFront(packet1);
    ASSERT_EQ(pEmptyList->getHeadData(), packet1);
    ASSERT_EQ(pEmptyList->getTailData(), packet1);
    ASSERT_EQ(pEmptyList->getNodeCount(), 1);
    pAdjEmptyList->pushFront(packet2);
    ASSERT_EQ(pAdjEmptyList->getHeadData(), packet2);
    ASSERT_EQ(pAdjEmptyList->getTailData(), packet2);
    ASSERT_EQ(pAdjEmptyList->getNodeCount(), 1);
}

TEST_F(ListTest, PushFrontToNonEmptyListOnlyChangesHeadAndCount) {
    pListWith1->pushFront(packet1);
    ASSERT_EQ(pListWith1->getHeadData(), packet1);
    ASSERT_EQ(pListWith1->getTailData(), packet0);
    ASSERT_EQ(pListWith1->getNodeCount(), 2);
    pAdjListWith1->pushFront(packet2);
    ASSERT_EQ(pAdjListWith1->getHeadData(), packet2);
    ASSERT_EQ(pAdjListWith1->getTailData(), packet0);
    ASSERT_EQ(pAdjListWith1->getNodeCount(), 2);
}

// PushBack Tests
TEST_F(ListTest, PushBackToEmptyListSetsHeadAndTailAndCount) {
    pEmptyList->pushBack(packet1);
    ASSERT_EQ(pEmptyList->getHeadData(), packet1);
    ASSERT_EQ(pEmptyList->getHeadData(), packet1);
    ASSERT_EQ(pEmptyList->getNodeCount(), 1);
    pAdjEmptyList->pushBack(packet2);
    ASSERT_EQ(pAdjEmptyList->getHeadData(), packet2);
    ASSERT_EQ(pAdjEmptyList->getHeadData(), packet2);
    ASSERT_EQ(pAdjEmptyList->getNodeCount(), 1);
}

TEST_F(ListTest, PushBackToNonEmptyListOnlyChangesTailAndCount) {
    pListWith1->pushBack(packet1);
    ASSERT_EQ(pListWith1->getHeadData(), packet0);
    ASSERT_EQ(pListWith1->getTailData(), packet1);
    ASSERT_EQ(pListWith1->getNodeCount(), 2);
    pAdjListWith1->pushBack(packet2);
    ASSERT_EQ(pAdjListWith1->getHeadData(), packet0);
    ASSERT_EQ(pAdjListWith1->getTailData(), packet2);
    ASSERT_EQ(pAdjListWith1->getNodeCount(), 2);
}

// PushAt, getDataAt Tests
TEST_F(ListTest, PushAtInvalidPositionDoesNotAlterList) {
    pListWith3->pushAt(packet0, -1);
    ASSERT_EQ(pListWith3->getNodeCount(), 3);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getNode(0), pListWith3->getHead());
    ASSERT_EQ(pListWith3->getDataAtNode(0), packet1);
    ASSERT_EQ(pListWith3->getTailData(), packet2);
}

TEST_F(ListTest, PushAt0){
    pAdjListWith3->pushAt(packet0, 0);
    ASSERT_EQ(pAdjListWith3->getHeadData(), packet0);
    ASSERT_EQ(pAdjListWith3->getDataAtNode(1), packet1);
    ASSERT_EQ(pAdjListWith3->getDataAtNode(2), packet2);
    ASSERT_EQ(pAdjListWith3->getTailData(), packet2);
    ASSERT_EQ(pAdjListWith3->getNodeCount(), 4);
}

TEST_F(ListTest, PushAtTail){
    pListWith3->pushAt(packet0, 3);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getDataAtNode(1), packet2);
    ASSERT_EQ(pListWith3->getDataAtNode(2), packet2);
    ASSERT_EQ(pListWith3->getTailData(), packet0);
    ASSERT_EQ(pListWith3->getNodeCount(), 4);
}

TEST_F(ListTest, PushAtMiddle){
    pAdjListWith3->pushAt(packet0, 2);
    ASSERT_EQ(pAdjListWith3->getHeadData(), packet1);
    ASSERT_EQ(pAdjListWith3->getDataAtNode(1), packet2);
    ASSERT_EQ(pAdjListWith3->getDataAtNode(2), packet0);
    ASSERT_EQ(pAdjListWith3->getTailData(), packet2);
    ASSERT_EQ(pAdjListWith3->getNodeCount(), 4);
}

// PopFront Tests
TEST_F(ListTest, PopFrontEmptyListDoesNothing) {
    pEmptyList->popFront();
    ASSERT_EQ(pEmptyList->getNodeCount(), 0);
    ASSERT_EQ(pEmptyList->getHeadData(), nullptr);
    ASSERT_EQ(pEmptyList->getTailData(), nullptr);
}

TEST_F(ListTest, PopFrontListWith1NodeSetsHeadAndTailToNull) {
    pAdjListWith1->popFront();
    ASSERT_EQ(pAdjListWith1->getNodeCount(), 0);
    ASSERT_EQ(pAdjListWith1->getHeadData(), nullptr);
    ASSERT_EQ(pAdjListWith1->getTailData(), nullptr);
}

TEST_F(ListTest, PopFrontNonEmptyListRemovesHeadAndDecreasesCount) {
    pListWith3->popFront();
    ASSERT_EQ(pListWith3->getNodeCount(), 2);
    ASSERT_EQ(pListWith3->getHeadData(), packet2);
    ASSERT_EQ(pListWith3->getTailData(), packet2);
}

// PopBack Tests
TEST_F(ListTest, PopBackEmptyListDoesNothing) {
    pAdjEmptyList->popBack();
    ASSERT_EQ(pAdjEmptyList->getNodeCount(), 0);
    ASSERT_EQ(pAdjEmptyList->getHeadData(), nullptr);
    ASSERT_EQ(pAdjEmptyList->getTailData(), nullptr);
}

TEST_F(ListTest, PopBackListWith1NodeSetsHeadAndTailToNull) {
    pListWith1->popBack();
    ASSERT_EQ(pListWith1->getNodeCount(), 0);
    ASSERT_EQ(pListWith1->getHeadData(), nullptr);
    ASSERT_EQ(pListWith1->getTailData(), nullptr);
}

TEST_F(ListTest, PopBackNonEmptyListRemovesTailAndDecreasesCount) {
    pAdjListWith3->popBack();
    ASSERT_EQ(pAdjListWith3->getNodeCount(), 2);
    ASSERT_EQ(pAdjListWith3->getHeadData(), packet1);
    ASSERT_EQ(pAdjListWith3->getTailData(), packet2);
}

// PopAt Tests
TEST_F(ListTest, PopAtInvalidPositionDoesNotAlterList) {
    pListWith3->popAt(-1);
    ASSERT_EQ(pListWith3->getNodeCount(), 3);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getDataAtNode(1), packet2);
    ASSERT_EQ(pListWith3->getTailData(), packet2);
}

TEST_F(ListTest, PopAt0){
    pAdjListWith3->popAt(0);
    ASSERT_EQ(pAdjListWith3->getHeadData(), packet2);
    ASSERT_EQ(pAdjListWith3->getTailData(), packet2);
    ASSERT_EQ(pAdjListWith3->getNodeCount(), 2);
}

TEST_F(ListTest, PopAtTail){
    pListWith3->popAt(2);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getTailData(), packet2);
    ASSERT_EQ(pListWith3->getNodeCount(), 2);
}

TEST_F(ListTest, PopAtMiddle){
    pAdjListWith3->popAt(1);
    ASSERT_EQ(pAdjListWith3->getHeadData(), packet1);
    ASSERT_EQ(pAdjListWith3->getTailData(), packet2);
    ASSERT_EQ(pAdjListWith3->getNodeCount(), 2);
}

// SetDataAtNode Tests
TEST_F(ListTest, SetDataAtNodeInvalidPositionDoesNotAlterList) {
    pListWith3->setDataAtNode(-1, packet1);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getDataAtNode(1), packet2);
    ASSERT_EQ(pListWith3->getTailData(), packet2);
    cout<<"11"<<endl;
}

TEST_F(ListTest, SetDataAtNode0){
    cout<<"a"<<endl;
    pAdjListWith3->setDataAtNode(0, packet0);
    cout<<"a"<<endl;
    ASSERT_EQ(pAdjListWith3->getHeadData(), packet0);
    cout<<"a"<<endl;
    ASSERT_EQ(pAdjListWith3->getDataAtNode(1), packet2);
    cout<<"a"<<endl;
    ASSERT_EQ(pAdjListWith3->getTailData(), packet2);
}

TEST_F(ListTest, SetDataAtNodeTail){
    pListWith3->setDataAtNode(2, packet0);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getDataAtNode(1), packet2);
    ASSERT_EQ(pListWith3->getTailData(), packet0);
}

TEST_F(ListTest, SetDataAtNodeMiddle){
    pAdjListWith3->setDataAtNode(1, packet0);
    ASSERT_EQ(pAdjListWith3->getHeadData(), packet1);
    ASSERT_EQ(pAdjListWith3->getDataAtNode(1), packet0);
    ASSERT_EQ(pAdjListWith3->getTailData(), packet2);
}

// SwapNodesAt Tests
TEST_F(ListTest, SwapNodesAtInvalidPositionsDoesNotAlterList) {
    pListWith3->swapNodesAt(-1, 5);
    ASSERT_EQ(pListWith3->getHeadData(), packet1);
    ASSERT_EQ(pListWith3->getDataAtNode(1), packet2);
    ASSERT_EQ(pListWith3->getTailData(), packet2);
}

TEST_F(ListTest, SwapNodesAtSamePositionDoesNotAlterList) {
    pAdjListWith3->swapNodesAt(0, 0);
    ASSERT_EQ(pAdjListWith3->getHeadData(), packet1);
    ASSERT_EQ(pAdjListWith3->getDataAtNode(1), packet2);
    ASSERT_EQ(pAdjListWith3->getTailData(), packet2);
}

TEST_F(ListTest, SwapNodesAt0And1){
    pListWith3->swapNodesAt(0, 2);
    ASSERT_EQ(pListWith3->getHeadData(), packet2);
    ASSERT_EQ(pListWith3->getDataAtNode(1), packet2);
    ASSERT_EQ(pListWith3->getTailData(), packet1);
}

// getDataAtNode Tests
TEST_F(ListTest, GetDataAtNodeInvalidPositionReturnsNullptr) {
    ASSERT_EQ(pAdjEmptyList->getDataAtNode(-1), nullptr);
    ASSERT_EQ(pAdjEmptyList->getDataAtNode(0), nullptr);
    ASSERT_EQ(pAdjEmptyList->getDataAtNode(1), nullptr);
}

// getPos Tests
TEST_F(ListTest, GetPos) {
    ASSERT_EQ(pEmptyList->getPos(packet1), -1);
    ASSERT_EQ(pListWith3->getPos(packet2), 1);
}

// isEmpty Tests
TEST_F(ListTest, IsEmpty) {
    ASSERT_TRUE(pAdjEmptyList->isEmpty());
    ASSERT_FALSE(pAdjListWith3->isEmpty());
}

// Contains Tests
TEST_F(ListTest, Contains) {
    ASSERT_FALSE(pEmptyList->contains(packet1));
    ASSERT_TRUE(pListWith3->contains(packet2));
    ASSERT_FALSE(pListWith3->contains(packet0));
}

// Print Tests
TEST_F(ListTest, PrintEmptyListPrintsNothing) {
    testing::internal::CaptureStdout();
    pAdjEmptyList->printList();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Start of list\nEnd of list\n");
}

TEST_F(ListTest, PrintNonEmptyListPrintsData) {
    testing::internal::CaptureStdout();
    pListWith3->printList();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Start of list\nPacket 1\nPacket 2\nPacket 2\nEnd of list\n");
}