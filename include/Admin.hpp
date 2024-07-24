#pragma once

#include "Network.hpp"

class Admin {
private:
    List<Node<Router>> *routers;
    Network *network;
    int BW = 2;
    int maxPageLength = 5;
    int probability = 20;
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
    bool checkCounter();
    void setBW(int bw);
    void setTerminals(int term);
    void setRoutersTerminals();
    void setProbability(int prob);
    void setMaxPageLength(int length);
    void printRouters();
    List<Node<Router>>* getRouters();
    Network* getNetwork();
};