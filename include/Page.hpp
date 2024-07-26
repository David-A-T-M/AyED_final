#pragma once

#include "..\include\Packet.hpp"
#include "..\include\List.hpp"
#include "..\include\Node.hpp"

using namespace std;

/**
 * @class Page
 * @brief Class to represent a page made of packets, which are created when it's instantiated.
 *        Inherits from List<Node<Packet>>.
 *        Stores a reference to origin and destination IPs. Also has a page ID for its packets to be identified
 *        and page length for the amount of packets it holds.
 */
class Page : public List<Node<Packet>>{
private:
    const int cPageID;                          /**< originIP+numberOfPageSent */
    const int cPageLength;                      /**< Page length in packets */
    const IPAddress& rOriginIP;                 /**< Reference to the sender Terminal IP */
    const IPAddress& rDestinationIP;            /**< Reference to the destination Terminal IP */
public:
    /**
     * @brief Constructor for the Page class. Initializes a new Page instance with specified parameters and populates it with Packet objects.
     * @param cPageID Unique identifier for the page.
     * @param cPageLength The number of packets the page will contain.
     * @param rOriginIP The origin IP address for the page.
     * @param rDestinationIP The destination IP address for the page.
     */
    Page(int cPageID, int cPageLength, const IPAddress &rOriginIP, const IPAddress &rDestinationIP);

    /**
     * @brief Constructor. Initializes a new Page instance with a list of packets.
     * @param packets Pointer to a list of packets to be used to build the page.
     */
    explicit Page(List<Node<Packet>>* packets);

    /**
     * @brief Default destructor
     */
    ~Page();

    /**
     * @brief Retrieves the page ID.
     * @return The unique identifier of the page.
     */
    int getPageID() const;

    /**
     * @brief Retrieves the length of the page in terms of the number of packets.
     * @return The number of packets in the page.
     */
    int getPageLength() const;

    /**
     * @brief Retrieves the origin IP address of the page.
     * @return A constant reference to the origin IP address.
     */
    const IPAddress& getOriginIP() const;

    /**
     * @brief Retrieves the destination IP address of the page.
     * @return A constant reference to the destination IP address.
     */
    const IPAddress& getDestinationIP() const;

    /**
     * @brief Prints the details of the page, including its ID, packets, and length.
     */
    void print() const;
};