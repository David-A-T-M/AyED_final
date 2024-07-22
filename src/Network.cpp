#include "Network.hpp"

Network::Network() : routers(), adjLists() {}

Network::Network(List<Node<Router>> *routers, int complexity) : routers(routers), adjLists() {
    for (int i = 0; i < routers->getNodeCount(); i++) {
        Router *router = routers->getDataAtNode(i);
        adjLists.pushBack(router->getAdjacencyList());
        generateRandomNetwork(complexity);
    }
}

Network::~Network() {
    Node<Router> *curr = routers->getHead();
    while(curr){
        delete curr->getData();
        curr = curr->getNext();
    }
}

void Network::recalculateRoutes() {
    cout << "Recalculating routes..." << endl << endl;
    for (int i = 0; i < routers->getNodeCount(); i++) {
        vector<int> parents = dijkstra(i);
        for (int j = 0; j < parents.size(); j++) {
            cout << parents[j] << " ";
        }
        cout << endl;
        fillNextHop(i, parents);
    }
    for (int i = 0; i < routers->getNodeCount(); i++) {
        Router *router = routers->getDataAtNode(i);
        router->checkQueues();
    }
}

vector<int> Network::dijkstra(int start) {
    int nodeCount = routers->getNodeCount();
    vector<bool> visited(nodeCount, false);
    vector<int> dist(nodeCount, INF);
    vector<int> parents(nodeCount, 0);
    dist[start] = 0;                        // Set the Weight from the starting router to itself to 0
    parents[start] = start;                 // Set the parent of the starting router to itself
    Router *nearest;                      // Pointer to the nearest router in the actual iteration
    int adjNode;                        // Position of the current adjacent node
    int adjWeight;                      // Weight of the current adjacent node
// Iteration for each non-visited router with the minimum distance
    for(int i = 0; i < adjLists.getNodeCount(); i++){
        int locDist = INF;
        int distNearest = 0;                                            // termina siendo la pos del router más cercano
        for(int j = 0; j < adjLists.getNodeCount(); j++) {  // este for es el getMinDist()
            if (!visited[j] && dist[j] < locDist) {
                locDist = dist[j];
                distNearest = j;
            }
        }
        visited[distNearest] = true;         // Mark the nearest router as visited
        nearest = routers->getDataAtNode(distNearest);    // Get the pointer to the nearest router
        //distNearest = locDist;              // Get the weight to the nearest router
        auto *currNode = nearest->getAdjacencyList()->getHead();
        while(currNode){
            auto *adjRouter = currNode->getData();
            adjWeight = currNode->getVal();
            adjNode = routers->getPos(adjRouter);
            if(!visited[adjNode] && locDist + adjWeight < dist[adjNode]){
                dist[adjNode] = locDist + adjWeight;
                parents[adjNode] = distNearest;
            }
            currNode = currNode->getNext();
        }
    }
    return parents;
}

void Network::fillNextHop(int posRouter, vector<int> parent) {
    Router *startRouter = routers->getDataAtNode(posRouter);
    for (int i = 0; i < routers->getNodeCount(); i++) {
        if (i == posRouter) {
            startRouter->setNextHop(i, posRouter);
        } else {
            int current = i;
            while (parent[current] != posRouter) {
                current = parent[current];
            }
            startRouter->setNextHop(i, current);
        }
    }
}

bool Network::isConnected(Router *router1, Router *router2) {
    return router1->getAdjacencyList()->contains(router2);
}

void Network::connectRouters(Router* router1, Router* router2) {
    if (*router1 == *router2) {
        return;
    }
    List<AdjNode<Router>> *list1 = router1->getAdjacencyList();
    List<AdjNode<Router>> *list2 = router2->getAdjacencyList();
    if (!list1->contains(router2)) {
        list1->pushBack(router2);
        list2->pushBack(router1);
        router1->getAdjRoutersQueues()->pushBack(new Queue<Node<Packet>>());
        router2->getAdjRoutersQueues()->pushBack(new Queue<Node<Packet>>());
    }
}

void Network::initializeNetworkConnections(){
    if (routers->getNodeCount() < 2) {
        return;
    }
    srand(time(nullptr));
    int routersAlreadyConnected = 1;
    connectRouters(routers->getDataAtNode(0), routers->getDataAtNode(1));
    for (int i = 2; i < routers->getNodeCount(); i++) {
        Router *router = routers->getDataAtNode(i);
        int randPos = rand() % routersAlreadyConnected;
        connectRouters(routers->getDataAtNode(randPos), router);
        routersAlreadyConnected++;
    }
}

void Network::generateAdditionalRandomConnections(){
    int nodeCount = routers->getNodeCount();
    if (nodeCount < 3) {
        return;
    }
    srand(time(nullptr));
    for (int i = 0; i < nodeCount; i++) {
        Router *router = routers->getDataAtNode(i);
        int randPos;
        do {
            randPos = rand() % nodeCount;
        } while (randPos == i);
        connectRouters(routers->getDataAtNode(randPos), router);
    }
}

void Network::generateRandomNetwork(int iter) {
    int defaultIter = iter;
    if(iter > 20 || iter < 0){
        defaultIter = 1;
    }
    initializeNetworkConnections();
    for (int i = 0; i < defaultIter; ++i) {
        generateAdditionalRandomConnections();
    }
}

List<Node<List<AdjNode<Router>>>>* Network::getAdjLists() {
    return &adjLists;
}