#pragma once

#include "IPAddress.hpp"

/**
 * @class Packet
 * @brief Represents a packet that forms part of a page. Stores all the information from the page it belongs to,
 *        including its position within the page, and a priority assigned by the router. This priority is used to determine
 *        the packet's transmission priority. Packets are the fundamental units used by routers for data transmission.
 */
class Packet {
private:
    const int cPageID;                              /**< ID of the page that the packet belongs to. */
    const int cPagePosition;                        /**< Position of the packet in the page. */
    const int cPageLength;                          /**< Length of the page. */
    int routerPriority;                             /**< Priority of the packet in the router. */
    const IPAddress& rDestinationIP;                /**< Reference to the destination terminal IP. */
    const IPAddress& rOriginIP;                     /**< Reference to the origin terminal IP. */

public:
    /**
     * @brief Constructor, called by the page constructor.
     * @param pageID ID of the page that the packet belongs to.
     * @param pagePosition Position of the packet in the page.
     * @param routerPriority Priority of the packet in the router.
     * @param destinationIP Reference to the destination terminal IP.
     * @param originIP Reference to the origin terminal IP.
     */
    Packet(int pageID, int pagePosition, int pageLength, int routerPriority, const IPAddress &destinationIP, const IPAddress &originIP);
    /**
     * @brief Default Destructor.
     */
    ~Packet();
    /**
     * @brief Sets the router priority.
     * @param routPri Router priority.
     */
    void setRouterPriority(int routPri);
    /**
     * @brief Gets the page ID.
     * @return Page ID.
     */
    int getPageID() const;
    /**
     * @brief Gets the page position.
     * @return Page position.
     */
    int getPagePosition() const;
    /**
     * @brief Gets the length of the page the packet belongs to.
     * @return Page length.
     */
    int getPageLength() const;
    /**
     * @brief Gets the router priority it got assigned the last time it was received by a router.
     * @return Router priority
     */
    int getRouterPriority() const;
    /**
     * @brief Gets the IP of it's destination terminal.
     * @return Destination terminal IP.
     */
    const IPAddress& getDestinationIP() const;
    /**
     * @brief Gets the IP of the terminal that originated the packet.
     * @return Origin terminal IP.
     */
    const IPAddress& getOriginIP() const;
    /**
     * @brief Gets a string with it's position in the page.
     * @return "Packet xx".
     */
    string toString() const;
    /**
     * @brief Compares two packets.
     * @param packet Packet to compare with.
     * @return True if both packets have the same cPageID and cPagePosition, false otherwise.
     */
    bool operator==(const Packet&) const;
};