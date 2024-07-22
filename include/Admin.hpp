#pragma once

#include "Network.hpp"

class Admin {
private:
    List<Node<Router>> *routers;
    Network *network;
    int BW = 2;
    int terminals = 2;
    int counter = 0;
public:
    Admin();
    ~Admin();
    // generar un network aleatorio
    void randomNetwork(int routersQuantity, int complexity);
    void addUnconnectedRouter();
    void addRandomlyConnectedRouter();
    void sendPages();
    void sendFromQueues();
    void setBW(int bw);
    void setTerminals(int term);
    void printRouters();
    List<Node<Router>>* getRouters();
    Network* getNetwork();
};