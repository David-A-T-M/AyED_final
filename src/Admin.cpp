#include "Admin.hpp"

Admin::Admin() : network(nullptr), routers(nullptr) {}

Admin::~Admin() { //TODO: revisar que se elimine todo
    delete network;
    delete routers;
}

void Admin::randomNetwork(int routersQuantity, int complexity) {
    routers = new List<Node<Router>>();
    for (int i = 0; i < routersQuantity; i++) {
        auto *router = new Router(routers, i, terminals, routersQuantity);
        routers->pushBack(router);
    }
    network = new Network(routers, complexity);
}

void Admin::addUnconnectedRouter() {
    auto *router = new Router(routers, routers->getNodeCount(), terminals, routers->getNodeCount());
    routers->pushBack(router);
    network->getAdjLists()->pushBack(router->getAdjacencyList());
    for (int i = 0; i < routers->getNodeCount(); i++) {
        auto *router2 = routers->getDataAtNode(i);
        router2->addHopDest();
    }
} //TODO: forzar a que lo conecten en el main

void Admin::addRandomlyConnectedRouter() {
    auto *router = new Router(routers, routers->getNodeCount(), terminals, routers->getNodeCount());
    routers->pushBack(router);
    network->getAdjLists()->pushBack(router->getAdjacencyList());
    for (int i = 0; i < routers->getNodeCount(); i++) {
        auto *router2 = routers->getDataAtNode(i);
        router2->addHopDest();
    }
    network->connectRouters(router, routers->getDataAtNode(rand() % routers->getNodeCount()));
    network->connectRouters(router, routers->getDataAtNode(rand() % routers->getNodeCount()));
    network->connectRouters(router, routers->getDataAtNode(rand() % routers->getNodeCount()));
    cout<<"Router added and connected to "<<router->getAdjacencyList()->getNodeCount()<<" random routers"<<endl;
}

void Admin::sendPages() {
    for (int i = 0; i < routers->getNodeCount(); i++) {
        int rout = rand() % routers->getNodeCount();
        int term1 = rand() % terminals;
        int term2 = rand() % terminals;
        int length = (rand() % 3) + 2;
        bool willSend = rand() % 2;
        if (!willSend) {
            continue;
        }
        auto *router = routers->getDataAtNode(i);
        cout<<"Sending page from router "<<i<<" terminal "<<term1<<" to router "<<rout<<" terminal "<<term2<<" with length "<<length<<endl;
        router->getTerminals()->getDataAtNode(term1)->sendPage(
                length, routers->getDataAtNode(rout)->getTerminals()->getDataAtNode(term2)->getTerminalIp());
    }
}

void Admin::sendFromQueues() {
    for (int i = 0; i < routers->getNodeCount(); i++) {
        auto *router = routers->getDataAtNode(i);
        router->sendFromQueues(BW);
    }
    if (counter == 1) {
        network->recalculateRoutes();
        counter = 0;
    } else {
        counter++;
    }
}

void Admin::setBW(int bw) {
    BW = bw;
}

void Admin::setTerminals(int term) {
    terminals = term;
}

void Admin::printRouters() {
    for (int i = 0; i < routers->getNodeCount(); i++) {
        auto *router = routers->getDataAtNode(i);
        router->printRouterInfo();
        cout << endl;
    }
}

List<Node<Router>>* Admin::getRouters() {
    return routers;
}

Network* Admin::getNetwork() {
    return network;
}