#pragma once

#include "..\include\Terminal.hpp"
#include "..\include\Packet.hpp"
#include "..\include\AdjNode.hpp"
#include "..\include\Queue.hpp"
#include <vector>

/**
 * @class Router
 * @brief Represents a router in a network. The Router class manages the routing of packets and pages
 *        between terminals and other routers. It maintains lists of connected terminals, adjacent routers,
 *        and queues for packet transmission. The router can receive and send pages, disassemble pages into packets,
 *        and manage packet priorities. It also provides various methods to print router information
 *        and manage routing paths.
 */
class Router {
private:
    const IPAddress ip;                     /**< IP address of the router */
    List<Node<Router>> *routers;        /**< List of routers */
    List<Node<Terminal>> terminals;     /**< List of terminals connected to the router */
    List<Node<Queue<Node<Packet>>>> adjRoutersQueues;  /**< List of queues of packets to send to neighbor routers */
    List<AdjNode<Router>> adjacencyList;    /**< List of adjacent routers */
    List<Node<List<Node<Packet>>>> incompletePages; /**< List of Lists of packets of an incomplete page */
    vector<int> nextHop;                    /**< Vector of next hops to reach each router */
    int packetsReceived = 0;
    bool rp = false;        /**< Flag to check if the router received a page from a terminal in the last iteration */
    bool sp = false;        /**< Flag to check if the router sent a page to a terminal in the last iteration */
public:
    /**
     * @brief Constructor. Creates a Router object with a specified IP address, initializes all the lists as empty,
     *        creates a number of terminals.
     * @param routers Pointer to the list of routers.
     * @param modemIP IP address of the router.
     * @param numOfTerminals Number of terminals connected to the router.
     * @param numOfRouters Number of routers in the network.
     */
    Router(List<Node<Router>> *routers, int modemIP, int numOfTerminals, int numOfRouters);

    /**
     * @brief Destructor. Deletes all the terminals, queues and incomplete pages with their respective packets.
     */
    ~Router();

    /**
     * @brief Sets the position of the next router to send a packet to in the position of the destination router.
     * @param i Position of the destination router in the list of routers.
     * @param newA Position of the next router in the path to reach the destination.
     */
    void setNextHop(int i, int newA);

    /**
     * @brief Sets the priority of the packets in a page, based on the number of packets received.
     * @param page Pointer to the page that contains the packets to set the priority.
     */
    void setPacketPriority(Page *page);

    /**
     * @brief Sets the priority of the packet based on the number of packets received.
     * @param packet Pointer to the packet to set the priority.
     */
    void setPacketPriority(Packet *packet);

    /**
     * @brief Gets the list of queues of packets to send to neighbor routers.
     * @return Pointer to the list of queues of packets.
     */
    List<Node<Queue<Node<Packet>>>>* getAdjRoutersQueues();

    /**
     * @brief Gets the list of terminals connected to the router.
     * @return List of terminals.
     */
    List<Node<Terminal>>* getTerminals();

    /**
     * @brief  Gets the adjacency list of the router.
     * @return Adjacency list of the router.
     */
    List<AdjNode<Router>>* getAdjacencyList();

    /**
     * @brief Gets the number of packets received by the router.
     * @return Number of packets received.
     */
    int getPacketsReceived() const;

    /**
     * @brief Gets the position of the router in the list of routers using the IP address.
     * @param destRouterIP IP of the destination router.
     * @return Position of the router in the list of routers.
     */
    int getRouterPos(uint8_t destRouterIP);

    /**
     * @brief Increments the size of the nextHop vector.
     */
    void addHopDest();

    /**
     * @brief Receives a page, if the destination is a terminal connected to the router,
     *        it sends the page to the terminal. If the destination is another router,
     *        disassembles the page into packets, and enqueues them in the corresponding queue.
     * @param page Pointer to the page being received.
     */
    void receivePage(Page* page);

    /**
     * @brief Sends a page to a terminal connected to the router.
     * @param termPos Position of the terminal in the list of terminals.
     * @param page Pointer to the page being sent.
     */
    void sendPage(int termPos, Page *page);

    /**
     * @brief Receives a packet, sets the router priority, and enqueues the packet in the corresponding queue.
     *        If the packet is for a terminal connected to the router, it adds the packet to the waiting list.
     * @param packet Pointer to the packet being received.
     */
    void receivePacket(Packet *packet);

    /**
     * @brief Stores the package in a waiting list with the same page ID. If it does not exist, a new list is created.
     *        If the page is completed with this package, the page is sent.
     * @param packet Pointer to the packet being sent.
     */
    void packetForTerminal(Packet *packet);

    /**
     * @brief Builds a page with the packets in the list. The list gets deleted.
     * @param packets Pointer to the list of packets to build the page.
     * @return Pointer to the page built.
     */
    Page* buildPage(List<Node<Packet>> *packets);

    /**
     * @brief Checks if a page is complete.
     * @param i Position of the page in the list of incomplete pages.
     * @return True if the page is complete, false otherwise.
     */
    bool isPageComplete(int i);

    /**
     * @brief Sends a number of packets equal to the bandwidth from each queue to its respective router.
     * @param bandWith Bandwidth of the connection between routers.
     */
    void sendFromQueues(int bandWith);

    /**
     * @brief Checks each queue and packet to ensure they are in the correct queue after the path has been recalculated.
     *        If a packet is not in the correct queue, it moves the packet to the end of the appropriate queue.
     *        Finally, performs an insertion sort on each queue to maintain order.
     */
    void checkQueues();

    /**
     * @brief Sorts the packets in all the queues using insertion sort.
     */
    void insertionSort();

    /**
     * @brief Gets the IP address of the router.
     * @return IP address of the router.
     */
    const IPAddress& getIP();

    /**
     * @brief Prints the name of the router in a "Router + binary IP" format.
     */
    void printRouterName();

    /**
     * @brief Prints if the router received or sent a page in the last iteration.
     */
    void printActivity();

    /**
     * @brief Prints the adjacency list of the router.
     */
    void printAdjacencyList();

    /**
     * @brief Prints the terminals connected to the router.
     */
    void printTerminals();

    /**
     * @brief Prints the queues with their packets, if there are no packets, it prints "Empty".
     */
    void printQueues();

    /**
     * @brief Prints the incomplete pages with their packets, if any.
     */
    void printIncompletePages();

    /**
     * @brief Prints the name, the activity, the adjacency list, the terminals,
     *        the queues, and the incomplete pages of the router.
     */
    void printRouterInfo();

    /**
     * @brief Generates a string representation of the router, including its IP address in decimal format.
     * @return A string representation of the router.
     */
    string toString();

    /**
     * @brief Overloads the equality operator to compare two routers.
     * @param router Router to compare with.
     * @return True if the routers are equal, false otherwise.
     */
    bool operator==(const Router& router);
};