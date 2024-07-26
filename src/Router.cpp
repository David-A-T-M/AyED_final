#include "..\include\Router.hpp"

Router::Router(List<Node<Router>> *routers, int modemIP, int numOfTerminals, int numOfRouters)
    : ip(modemIP),
      routers(routers),
      terminals(),
      adjRoutersQueues(),
      adjacencyList(),
      incompletePages(),
      packetsReceived(0){
    for (int i = 0; i < numOfTerminals; i++) {
        terminals.pushBack(new Terminal(IPAddress(ip.getRouterIP(), i), this));
    }
    for (int i = 0; i < numOfRouters; i++) {
        nextHop.push_back(i);
    }
}

Router::~Router() {
    for (int i = 0; i < terminals.getNodeCount(); ++i) {    //Delete terminals
        delete terminals.getDataAtNode(i);
    }
    for (int i = 0; i < adjRoutersQueues.getNodeCount(); ++i) {     //Delete queues and every packet in them
        auto *queue = adjRoutersQueues.getDataAtNode(i);
        auto *node = queue->getHead();
        while (node) {
            delete node->getData();
            node = node->getNext();
        }
        delete queue;
    }
    for (int i = 0; i < incompletePages.getNodeCount(); ++i) {      //Delete lists and every packet in them
        auto *list = incompletePages.getDataAtNode(i);
        auto *node = list->getHead();
        while (node) {
            delete node->getData();
            node = node->getNext();
        }
        delete list;
    }
}

void Router::setNextHop(int i, int newA){
    nextHop[i] = newA;
}

void Router::setPacketPriority(Page *page) {
    for (int i = 0; i < page->getNodeCount(); ++i) {
        auto *packet = page->getDataAtNode(i);
        setPacketPriority(packet);
    }
}

void Router::setPacketPriority(Packet *packet) {
    packet->setRouterPriority(packetsReceived);
    packetsReceived++;
}

List<Node<Queue<Node<Packet>>>>* Router::getAdjRoutersQueues() {
    return &adjRoutersQueues;
}

List<Node<Terminal>>* Router::getTerminals() {
    return &terminals;
}

List<AdjNode<Router>> *Router::getAdjacencyList(){
    return &adjacencyList;
}

int Router::getPacketsReceived() const {
    return packetsReceived;
}

int Router::getRouterPos(uint8_t destRouterIP) {
    int routerPos;
    for (routerPos = 0; routerPos < routers->getNodeCount(); routerPos++) {
        uint8_t b = routers->getDataAtNode(routerPos)->getIP().getRouterIP();
        if(b == destRouterIP) {
            break;
        }
    }
    return routerPos;
}

void Router::addHopDest() {
    nextHop.push_back(0);
}

void Router::receivePage(Page* page) {
    uint8_t destIP = page->getDestinationIP().getRouterIP();
    if(destIP == ip.getRouterIP()) {
        int termPos = page->getDestinationIP().getTerminalIP();
        sendPage(termPos, page);
        return;
    }
    int a = 0;
    for(a = 0; a < routers->getNodeCount(); a++) {
        uint8_t b = routers->getDataAtNode(a)->getIP().getRouterIP();
        if(b == destIP) {
            break;
        }
    }
    Router *nextRouter = routers->getDataAtNode(nextHop[a]);
    int qPos = adjacencyList.getPos(nextRouter);
    setPacketPriority(page);
    adjacencyList.getNode(qPos)->addToVal(page->getNodeCount());
    adjRoutersQueues.getDataAtNode(qPos)->enqueueList(page);
    delete page;
    rp = true;
}

void Router::sendPage(int termPos, Page *page) {
    terminals.getDataAtNode(termPos)->receivePage(page);
    sp = true;
}

void Router::receivePacket(Packet *packet) {
    packet->setRouterPriority(packetsReceived);
    packetsReceived++;
    uint8_t destIP = packet->getDestinationIP().getRouterIP();
    if(destIP == ip.getRouterIP()) {
        packetForTerminal(packet);
        return;
    }
    int routerPos = getRouterPos(destIP);
    Router *nextRouter = routers->getDataAtNode(nextHop[routerPos]);
    int listPos = adjacencyList.getPos(nextRouter);
    adjacencyList.getNode(listPos)->addToVal(1);
    Queue<Node<Packet>> *queue = adjRoutersQueues.getDataAtNode(listPos);
    queue->enqueue(packet);
}

void Router::packetForTerminal(Packet *packet) {
    for (int i = 0; i < incompletePages.getNodeCount(); ++i) {
        auto *auxPacket = incompletePages.getDataAtNode(i)->getHeadData();
        if (auxPacket->getPageID() == packet->getPageID()) {
            incompletePages.getDataAtNode(i)->pushBack(packet);
            if (isPageComplete(i)) {
                auto *page = buildPage(incompletePages.getDataAtNode(i));
                sendPage(auxPacket->getDestinationIP().getTerminalIP(), page);
                incompletePages.popAt(i);
            }
            return;
        }
    }
    auto *newList = new List<Node<Packet>>();
    newList->pushBack(packet);
    incompletePages.pushBack(newList);
}

Page* Router::buildPage(List<Node<Packet>> *packets) {
    Page *page = new Page(packets);
        return page;
}

bool Router::isPageComplete(int i) {
    int packetsInList = incompletePages.getDataAtNode(i)->getNodeCount();
    int pageLength = incompletePages.getDataAtNode(i)->getHeadData()->getPageLength();
    return packetsInList == pageLength;
}

void Router::sendFromQueues(int bandWith) {
    for (int i = 0; i < adjacencyList.getNodeCount(); ++i) {
        auto *router = adjacencyList.getDataAtNode(i);
        auto *queue = adjRoutersQueues.getDataAtNode(i);
        for (int j = 0; j < bandWith; ++j) {
            if (queue->isEmpty()) {
                break;
            }
            auto *packet = queue->getHeadData();
            router->receivePacket(packet);
            adjacencyList.getNode(i)->addToVal(-1);
            queue->dequeue();
        }
    }
}

void Router::checkQueues() {
    for (int i = 0; i < adjRoutersQueues.getNodeCount(); ++i) {             // Iterates through all queues.
        auto *currQueue = adjRoutersQueues.getDataAtNode(i);
        auto *node = currQueue->getHead();
        while (node) {
            auto *packet = node->getData();
            int routerPos = getRouterPos(packet->getDestinationIP().getRouterIP());
            auto *nextRouter = routers->getDataAtNode(nextHop[routerPos]);
            int adjPos = adjacencyList.getPos(nextRouter);
            if (adjPos == i) {
                node = node->getNext();
                continue;
            } else {
                adjRoutersQueues.getDataAtNode(adjPos)->enqueue(packet);
                adjacencyList.getNode(adjPos)->addToVal(1);
                auto *auxNode = node->getNext();
                currQueue->popAt(currQueue->getPos(packet));
                adjacencyList.getNode(i)->addToVal(-1);
                node = auxNode;
            }
        }
    }
    insertionSort();
}

void Router::insertionSort() {
    for (int h = 0; h < adjRoutersQueues.getNodeCount(); ++h) {
        auto *queue = adjRoutersQueues.getDataAtNode(h);
        if (queue->getNodeCount() < 2) {
            continue;
        }
        for (int i = 1; i < queue->getNodeCount(); ++i) {     // Iterates through all queues.
            auto packet = queue->getDataAtNode(i);
            int currPriority = packet->getRouterPriority();
            int j = i - 1;
            while (j >= 0 && queue->getDataAtNode(j)->getRouterPriority() > currPriority) {
                j--;
            }
            if (j != i - 1) {
                queue->popAt(i);
                queue->pushAt(packet, j + 1);
            }
        }
    }
}

const IPAddress& Router::getIP() {
    return ip;
}

void Router::printRouterName() {
    cout<<ip.toString();
}

void Router::printActivity() {
    if (rp) {
        cout<<"Has received a page from a terminal"<<endl;
    }
    if (sp) {
        cout<<"Has sent a page to a terminal"<<endl;
    }
    rp = false;
    sp = false;
}

void Router::printAdjacencyList() {
    cout<<"Adjacency List: "<<endl;
    for (int i = 0; i < adjacencyList.getNodeCount(); ++i) {
        cout<<adjacencyList.getNode(i)->toString()<<endl;
    }
}

void Router::printTerminals() {
    cout<<"Terminals: "<<endl;
    for (int i = 0; i < terminals.getNodeCount(); ++i) {
        cout<<terminals.getDataAtNode(i)->toString()<<endl;
    }
}

void Router::printQueues() {
    cout<<"Queues: "<<endl;
    for (int i = 0; i < adjRoutersQueues.getNodeCount(); ++i) {
        cout << "To ";
        adjacencyList.getDataAtNode(i)->printRouterName();
        cout<<endl;
        Queue<Node<Packet>> *queue = adjRoutersQueues.getDataAtNode(i);
        if (queue->isEmpty()) {
            cout<<"Empty"<<endl;
            continue;
        }
        for (int j = 0; j < queue->getNodeCount(); ++j) {
            cout<<queue->getDataAtNode(j)->toString()<<"\t";
        }
        cout<<endl;
    }
}

void Router::printIncompletePages() {
    cout<<"Incomplete Pages: "<<endl;
    if (incompletePages.isEmpty()) {
        cout<<"Empty"<<endl;
        return;
    }
    for (int i = 0; i < incompletePages.getNodeCount(); ++i) {
        auto *list = incompletePages.getDataAtNode(i);
        cout<<"Page "<<list->getHeadData()->getPageID()<<" Length "<<list->getHeadData()->getPageLength()<<":\t";
        for (int j = 0; j < list->getNodeCount(); ++j) {
            cout<<to_string(list->getDataAtNode(j)->getPagePosition())<<"\t";
        }
        cout<<endl;
    }
}

void Router::printRouterInfo() {
    printRouterName();
    cout<<endl;
    printActivity();
    printAdjacencyList();
    printTerminals();
    printQueues();
    printIncompletePages();
}

string Router::toString() {
    return "Router: " + to_string(ip.getRouterIP());
}

bool Router::operator==(const Router &router) {
    return ip == router.ip;
}