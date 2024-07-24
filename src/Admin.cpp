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
}

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
        auto *router = routers->getDataAtNode(i);
        int rout = rand() % routers->getNodeCount();
        int term = rand() % terminals;
        int length = (rand() % (maxPageLength-2)) + 2;
        for (int j = 0; j < terminals; j++) {
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
    for (int i = 0; i < routers->getNodeCount(); i++) {
        auto *router = routers->getDataAtNode(i);
        router->sendFromQueues(BW);
    }
}

bool Admin::checkCounter() {
    if (counter == 1) {
        network->recalculateRoutes();
        counter = 0;
        return true;
    } else {
        counter++;
        return false;
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

void Admin::setMaxPageLength(int length) {
    maxPageLength = length;
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