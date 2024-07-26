#include "..\include\Admin.hpp"

Admin::Admin() : network(nullptr), routers(nullptr) {}

Admin::~Admin() {
    delete network;
    delete routers;
}

void Admin::setBW(int bw) {
    BW = bw;
}

void Admin::setTerminals(int term) {
    terminals = term;
}

void Admin::setRoutersTerminals() {
    int routTermCount = routers->getDataAtNode(0)->getTerminals()->getNodeCount();
    if (routTermCount < terminals) {
        for (int i = 0; i < routers->getNodeCount(); i++) {
            auto *router = routers->getDataAtNode(i);
            auto *routerTerminals = routers->getDataAtNode(i)->getTerminals();
            for (int j = 0; j < (terminals - routTermCount); j++) {
                routerTerminals->pushBack(new Terminal(IPAddress(router->getIP().getRouterIP(), routTermCount + j), router));
            }
        }
        printRouters();
    } else if (routTermCount > terminals) {
        cout << "New amount should be higher than current amount" << endl;
        //TODO: para implementarlo correctamente se deben recorrer las colas y eliminar los paquetes con destino a las terminales eliminadas
//            for (int k = 0; k < (routTermCount - terminals); k++) {
//                delete routerTerminals->getTailData();
//                routerTerminals->popBack();
//            }
    }

}

void Admin::setProbability(int prob) {
    probability = prob;
}

void Admin::setMaxPageLength(int length) {
    maxPageLength = length;
}

List<Node<Router>>* Admin::getRouters() {
    return routers;
}

Network* Admin::getNetwork() {
    return network;
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
}

void Admin::addRandomlyConnectedRouter() {
    auto *router = new Router(routers, routers->getNodeCount(), terminals, routers->getNodeCount());
    routers->pushBack(router);
    network->getAdjLists()->pushBack(router->getAdjacencyList());
    for (int i = 0; i < routers->getNodeCount(); i++) {
        auto *router2 = routers->getDataAtNode(i);
        router2->addHopDest();
    }
    int routerAmount = routers->getNodeCount();
    for (int i = -1; i < rand() % routerAmount; i++) {
        auto *router2 = routers->getDataAtNode(rand() % (routerAmount-1));
        network->connectRouters(router, router2);
    }
    cout<<"Router added and connected to "<<router->getAdjacencyList()->getNodeCount()<<" random routers"<<endl;
}

void Admin::sendPages() {
    for (int i = 0; i < routers->getNodeCount(); i++) {     // Iterates through all routers.
        auto *router = routers->getDataAtNode(i);
        int rout = rand() % routers->getNodeCount();        // Random destination router.
        int term = rand() % terminals;                      // Random destination terminal.
        int length = (rand() % (maxPageLength-2)) + 2;      // Random page length.
        for (int j = 0; j < terminals; j++) {               // Iterates through all terminals in the current router.
            bool willSend = (rand() % 100) < probability;
            auto *terminal = router->getTerminals()->getDataAtNode(j);
            if (!willSend) {
                continue;
            }
            cout<<"Sending page from router "<<i<<" terminal "<<j<<" to router "<<rout<<" terminal "<<term<<" with length "<<length<<endl;
            terminal->sendPage(length, routers->getDataAtNode(rout)->getTerminals()->getDataAtNode(term)->getTerminalIp());
        }
    }
}

void Admin::sendFromQueues() {
    for (int i = 0; i < routers->getNodeCount(); i++) {         // Iterates through all routers.
        auto *router = routers->getDataAtNode(i);
        router->sendFromQueues(BW);                    // Sends packets from the router's queues.
    }
}

bool Admin::checkCounter() {
    if (counter == 1) {         // If the counter reaches 1, recalculates routes.
        network->recalculateRoutes();
        counter = 0;            // Resets the counter.
        return true;
    } else {                    // Otherwise, increments the counter.
        counter++;
        return false;
    }
}

void Admin::printRouters() {
    for (int i = 0; i < routers->getNodeCount(); i++) {
        auto *router = routers->getDataAtNode(i);
        router->printRouterInfo();
        cout << endl;
    }
}