#pragma once

#include <iostream>
#include <bitset>
#include <cstdint>

using namespace std;
/**
 * @class IPAddress
 * @brief Represents an IP address that can be used for either a router or a terminal.
 *        For a router, it uses an 8-bit address. For a terminal, it combines the router's 8-bit address
 *        with an additional 8-bit terminal address, resulting in a 16-bit address.
 */
class IPAddress {
private:
    const uint8_t routerIP;         /**< Router IP. */
    const uint8_t terminalIP;       /**< Terminal IP */
    bool Router;                    /**< True if the IP is from a router */

public:
    /**
     * @brief Default Constructor
     */
    IPAddress();
    /**
     * @brief Constructor for a router IP
     * @param routerIP Router IP
     */
    explicit IPAddress(uint8_t routerIP);
    /**
     * @brief Constructor for a terminal IP
     * @param routerIP Router IP
     * @param terminalIP Terminal IP
     */
    IPAddress(uint8_t routerIP, uint8_t terminalIP);
    /**
     * @brief Default Destructor
     */
    ~IPAddress();
    /**
     * @brief Get the router IP
     * @return Router IP
     */
    uint8_t getRouterIP() const;
    /**
     * @brief Get the terminal IP
     * @return Terminal IP
     */
    uint8_t getTerminalIP() const;
    /**
     * @brief Checks if the IP is from a router
     * @return True if the IP is from a router, false if it is from a terminal
     */
    bool isRouter() const;
    /**
     * @brief Get a string representation of the IP
     * @return String representation of the IP
     */
    string toString() const;
    /**
     * @brief Compare two IP addresses
     * @param ip IP address to compare
     * @return True if the IP addresses are equal, false otherwise
     */
    bool operator==(const IPAddress &ip) const;
};