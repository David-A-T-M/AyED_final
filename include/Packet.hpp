/**
 * @class Packet
 * @brief Represents a packet that conforms a page. Stores the page ID, its position in the page,
 *        its priority in the router and the destination terminal IP
 */
#pragma once

#include "IPAddress.hpp"

class Packet {
private:
    const int cPageID;                              /**< ID of the page that the packet belongs to */
    const int cPagePosition;                        /**< Position of the packet in the page */
    int routerPriority;                             /**< Priority of the packet in the router */
    const IPAddress& rDestinationIP;                /**< Reference to the destination terminal IP */

public:
    /**
     * @brief Constructor, called by the page constructor
     * @param pageID ID of the page that the packet belongs to
     * @param pagePosition Position of the packet in the page
     * @param routerPriority Priority of the packet in the router
     * @param destinationIP Reference to the destination terminal IP
     */
    Packet(int pageID, int pagePosition, int routerPriority, const IPAddress &destinationIP);
    /**
     * @brief Default Destructor
     */
    ~Packet();
    /**
     * @brief gets the page ID
     * @return Integer Page ID
     */
    int getPageID() const;
    /**
     * @brief gets the page position
     * @return Integer Page position
     */
    int getPagePosition() const;
    /**
     * @brief gets the router priority
     * @return Integer Router priority
     */
    int getRouterPriority() const;
    /**
     * @brief gets the destination IP
     * @return Constant reference to the destination terminal IP
     */
    const IPAddress& getDestinationIP() const;
    /**
     * @brief returns a string with the packet1 cPagePosition
     * @return String with the "packet + cPagePosition"
     */
    string toString() const;
    /**
     * @brief compares two packets
     * @param packet Packet to compare with
     * @return True if both packets have the same cPageID and cPagePosition, false otherwise
     */
    bool operator==(const Packet&) const;
};