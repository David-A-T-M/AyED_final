/*#include <gtest/gtest.h>
#include "Router.hpp"

class RouterTest : public ::testing::Test {
protected:
    List<Node<Router>> *routers{};
    Router *router1{}, *router2{}, *router3{}, *router4{}, *router5{};
    Page *page1{}, *page2{};
    Packet *packet1{}, *packet2{}, *packet3{}, *packet4{}, *packet5{};
    void SetUp() override {
        routers = new List<Node<Router>>();
        router1 = new Router(routers, 1, 2, 5);
        router2 = new Router(routers, 2, 2, 5);
        router3 = new Router(routers, 3, 2, 5);
        router4 = new Router(routers, 4, 2, 5);
        router5 = new Router(routers, 5, 2, 5);
        routers->pushBack(router1);
        routers->pushBack(router2);
        routers->pushBack(router3);
        routers->pushBack(router4);
        routers->pushBack(router5);
        router1->getAdjacencyList()->pushBack(router2);
        router1->getAdjRoutersQueues()->pushBack(new Queue<Node<Packet>>());
        router1->getAdjacencyList()->pushBack(router3);
        router1->getAdjRoutersQueues()->pushBack(new Queue<Node<Packet>>());
        router1->getAdjacencyList()->pushBack(router4);
        router1->getAdjRoutersQueues()->pushBack(new Queue<Node<Packet>>());
        router2->getAdjacencyList()->pushBack(router1);
        router2->getAdjRoutersQueues()->pushBack(new Queue<Node<Packet>>());
        router2->getAdjacencyList()->pushBack(router5);
        router2->getAdjRoutersQueues()->pushBack(new Queue<Node<Packet>>());
        router3->getAdjacencyList()->pushBack(router1);
        router3->getAdjRoutersQueues()->pushBack(new Queue<Node<Packet>>());
        router3->getAdjacencyList()->pushBack(router4);
        router3->getAdjRoutersQueues()->pushBack(new Queue<Node<Packet>>());
        router3->getAdjacencyList()->pushBack(router5);
        router3->getAdjRoutersQueues()->pushBack(new Queue<Node<Packet>>());
        router4->getAdjacencyList()->pushBack(router1);
        router4->getAdjRoutersQueues()->pushBack(new Queue<Node<Packet>>());
        router4->getAdjacencyList()->pushBack(router3);
        router4->getAdjRoutersQueues()->pushBack(new Queue<Node<Packet>>());
        router5->getAdjacencyList()->pushBack(router2);
        router5->getAdjRoutersQueues()->pushBack(new Queue<Node<Packet>>());
        router5->getAdjacencyList()->pushBack(router3);
        router5->getAdjRoutersQueues()->pushBack(new Queue<Node<Packet>>());
        router1->setNextHop(4, 2);
        page1 = new Page(1001001, 5, router1->getTerminals()->getDataAtNode(0)->getTerminalIp(),
                         router1->getTerminals()->getDataAtNode(1)->getTerminalIp());
        page2 = new Page(1001002, 5, router1->getTerminals()->getDataAtNode(0)->getTerminalIp(),
                            router5->getTerminals()->getDataAtNode(1)->getTerminalIp());
        packet1 = new Packet(2001003, 4, 3, 0,router1->getTerminals()->getDataAtNode(1)->getTerminalIp(),
                             router2->getTerminals()->getDataAtNode(0)->getTerminalIp());
        packet2 = new Packet(2001004, 4, 3, 0,router3->getTerminals()->getDataAtNode(0)->getTerminalIp(),
                             router2->getTerminals()->getDataAtNode(0)->getTerminalIp());
        packet3 = new Packet(2001005, 3, 3, 0,router2->getTerminals()->getDataAtNode(0)->getTerminalIp(),
                                router2->getTerminals()->getDataAtNode(0)->getTerminalIp());
        packet4 = new Packet(2001006, 0, 2, 0,router1->getTerminals()->getDataAtNode(0)->getTerminalIp(),
                                router2->getTerminals()->getDataAtNode(0)->getTerminalIp());
        packet5 = new Packet(2001006, 1, 2, 0,router1->getTerminals()->getDataAtNode(0)->getTerminalIp(),
                                router2->getTerminals()->getDataAtNode(0)->getTerminalIp());
        router2->setNextHop(2, 0);
        router2->setNextHop(3, 0);
        router3->setNextHop(1, 0);
    }
    void TearDown() override {

    }
};

    //cout<<"a"<<endl;
TEST_F(RouterTest, constructor) {
    //EXPECT_EQ(router1->getIP().getRouterIP(), 1);
    //router1->printRouterInfo();
    //router2->printRouterInfo();
    //router3->printRouterInfo();
    //router4->printRouterInfo();
    //router5->printRouterInfo();
    //cout<<endl;
    router1->receivePage(page1);
    router1->receivePage(page2);
    router1->receivePacket(packet3);
    router1->receivePacket(packet5);
    router1->getTerminals()->getDataAtNode(1)->sendPage(3, router2->getTerminals()->getDataAtNode(1)->getTerminalIp());
    router1->printRouterInfo();
    cout<<endl;
    router1->setNextHop(4, 1);
    router1->checkQueues();
    router1->receivePacket(packet1);
    router1->receivePacket(packet2);
    router1->receivePacket(packet4);
    router1->printRouterInfo();
    router1->sendFromQueues(2);
    router1->getTerminals()->getDataAtNode(0)->sendPage(3, router3->getTerminals()->getDataAtNode(1)->getTerminalIp());
    router1->getTerminals()->getDataAtNode(1)->sendPage(3, router5->getTerminals()->getDataAtNode(1)->getTerminalIp());
    cout<<endl;
    router1->printRouterInfo();
    cout<<endl;
    router2->printRouterInfo();
    cout<<endl;
    router3->printRouterInfo();
}
*/