#pragma once

#include "..\include\Network.hpp"
/**
 * @class Admin
 * @brief Manages the network and the routers.
 *
 * The Admin class is responsible for managing the network and the routers within it.
 * It provides methods to set various network parameters such as bandwidth, number of terminals,
 * probability of sending a page, and maximum page length. The class also includes methods to
 * create a random network, add routers (both unconnected and randomly connected), send pages
 * and packets, it updates the routes every two iterations, and print information about the routers.
 */
class Admin {
private:
    List<Node<Router>> *routers;
    Network *network;
    int BW = 2;
    int maxPageLength = 5;
    int probability = 25;
    int terminals = 2;
    int counter = 0;
public:
    /**
     * Constructor. Initializes the network and the routers list as nullptr.
     */
    Admin();

    /**
     * Destructor. Deletes the network and the routers list.
     */
    ~Admin();

    /**
     * @brief Sets the bandwidth between routers.
     * @param bw The bandwidth value to set.
     */
    void setBW(int bw);

    /**
     * @brief Sets the number of terminals for each router.
     * @param term The number of terminals to set.
     */
    void setTerminals(int term);

    /**
     * @brief Creates terminals for each router, if they don't exist.
     */
    void setRoutersTerminals();

    /**
     * @brief Sets the probability of sending a page.
     * @param prob The probability value to set.
     */
    void setProbability(int prob);

    /**
     * @brief Sets the maximum length of a page.
     * @param length The maximum page length to set.
     */
    void setMaxPageLength(int length);

    /**
     * @brief Gets the list of routers in the network.
     * @return A pointer to the list of routers.
     */
    List<Node<Router>>* getRouters();

    /**
     * @brief Gets the network object.
     * @return A pointer to the network object.
     */
    Network* getNetwork();

    /**
     * @brief Creates a random network with a specified number of routers and complexity.
     * @param routersQuantity The number of routers to create.
     * @param complexity The complexity level of the network connections.
     */
    void randomNetwork(int routersQuantity, int complexity);

    /**
     * @brief Adds an unconnected router to the network. Increases the size of every router's nextHop vector.
     */
    void addUnconnectedRouter();

    /**
     * @brief Adds a router to the network and connects it to random routers.
     */
    void addRandomlyConnectedRouter();

    /**
     * @brief Sends pages from terminals of each router to random destinations.
     */
    void sendPages();

    /**
     * @brief Sends packets from the non empty queues of each router.
     */
    void sendFromQueues();

    /**
     * @brief Checks and updates the counter, recalculating routes if necessary.
     * @return True if routes were recalculated, false otherwise.
     */
    bool checkCounter();

    /**
     * @brief Prints information about all routers in the network.
     */
    void printRouters();
};