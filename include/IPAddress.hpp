/**
 * @class IPAddress
 * @brief Represents an IP address that can be used for either a modem or a terminal.
 *        For a modem, it uses an 8-bit address. For a terminal, it combines the modem's 8-bit address
 *        with an additional 8-bit terminal address, resulting in a 16-bit address.
 */
#pragma once

#include <iostream>
#include <bitset>
#include <cstdint>

using namespace std;

class IPAddress {
private:
    const uint8_t modemIP;         /**< Modem IP */
    const uint8_t terminalIP;      /**< Terminal IP */
    bool Modem;                    /**< True if the IP is from a modem */

public:
    /**
     * @brief Constructor for a modem IP
     * @param modemIP Modem IP
     */
    explicit IPAddress(uint8_t modemIP);
    /**
     * @brief Constructor for a terminal IP
     * @param modemIP Modem IP
     * @param terminalIP Terminal IP
     */
    IPAddress(uint8_t modemIP, uint8_t terminalIP);
    /**
     * @brief Default Destructor
     */
    ~IPAddress();
    /**
     * @brief Get the modem IP
     * @return Modem IP
     */
    uint8_t getModemIP() const;
    /**
     * @brief Get the terminal IP
     * @return Terminal IP
     */
    uint8_t getTerminalIP() const;
    /**
     * @brief Check if the IP is from a modem
     * @return True if the IP is from a modem, false if it is from a terminal
     */
    bool isModem() const;
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