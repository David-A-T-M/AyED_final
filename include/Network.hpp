#pragma once

#include "..\include\Router.hpp"
#include "..\include\AdjNode.hpp"
#include <vector>

#define INF 9999

using namespace std;

/**
 * @class Network
 * @brief Manages a network of routers, providing functionalities for network topology and routing. The Network class
 *        encapsulates a collection of routers and their connections, simulating a network environment. It allows
 *        for the initialization of the network with a set of routers, the establishment of connections between
 *        routers, and the calculation of routing paths using Dijkstra's algorithm. The class supports
 *        dynamic network configurations, enabling the addition of new connections and the recalibration
 *        of routing paths as the network evolves.
 */
class Network {
private:
    List<Node<Router>> *routers;            /**< List of routers in the network */
    List<Node<List<AdjNode<Router>>>> adjLists;         /**< List of every router's adjacency list */
public:
    /**
     * @brief Default constructor. Initializes an empty list of routers and an empty list of adjacency lists.
     */
    Network();

    /**
     * @brief Constructor, initializes the list of routers with the routers received as a parameter. For each router,
     *        gets the adjacency list and adds it to the list of adjacency lists. Then generates a random network.
     * @param routers List of routers to work with
     */
    explicit Network(List<Node<Router>> *routers, int complexity);

    /**
     * @brief Destructor. Traverses the list of routers, deleting each router. Deletes all the nodes in routers,
     *        but does not delete the list itself.
     */
    ~Network();

    /**
     * @brief Gets the list every router's adjacency list.
     * @return List of adjacency lists.
     */
    List<Node<List<AdjNode<Router>>>>* getAdjLists();

    /**
     * @brief Connects two routers bidirectionally with a default weight of 1. Adjacency list in both routers is updated.
     *        If both routers are the same, or they are already connected, the method does nothing.
     * @param router1 Pointer to the first router
     * @param router2 Pointer to the second router
     */
    void connectRouters(Router *router1, Router *router2);

    /**
     * @brief This method constructs a random network where each existing router is randomly connected
     *        to one of the already connected routers, ensuring there are no isolated routers.
     */
    void initializeNetworkConnections();

    /**
     * @brief Traverse the list of routers, generating a potential new connection for each router.
     */
    void generateAdditionalRandomConnections();

    /**
     * @brief Generates a random network with a specified level of connectivity (0-20).
     *        The higher the level, the more connected the network will be.
     *        If the parameter is out of bounds, 1 is used as the default value.
     * @param iter Number of iterations to generate the network, must be in range [0, 20]
     */
    void generateRandomNetwork(int iter);

    /**
     * @brief Applies Dijkstra's algorithm to calculate the shortest path from a given router
     *        to all other routers, generating a vector of parents for each router in the network.
     * @param start Position of the starting router in the list of routers
     * @return Vector of parents of each router in the path
     */
    vector<int> dijkstra(int start);

    /**
     * @brief For a given router, calculates the next hop to reach each router in the network
     *        and stores it in the nextHop vector of the router.
     * @param posRouter Position of the router in the list of routers
     * @param parent Vector of parents of each router in the path
     */
    void fillNextHop(int posRouter, vector<int> parent);

    /**
     * @brief Recalculates the shortest path from each router to all other routers in the network,
     *        updating the nextHop vector of each router accordingly.
     */
    void recalculateRoutes();

    /**
     * @brief Checks if two routers are connected.
     * @param router1 Pointer to the first router
     * @param router2 Pointer to the second router
     * @return True if the routers are connected, false otherwise
     */
    bool isConnected(Router *router1, Router *router2);
};