//
// Created by David on 08/07/2024.
//
#pragma once

#include "IPAddress.hpp"

class Packet {
private:
    const int cPageID;                              // Page ID (originIP+numberOfPageSent)
    const int cPagePosition;                        // Packet position in the page
    int routerPosition;                             // Router position in the path
    const IPAddress& rDestinationIP;                // Reference to destination terminal IP

public:
    Packet(int, int, int, const IPAddress&);        // Constructor, called by the page constructor
    ~Packet();                                      // Destructor
    int getPageID() const;
    int getPagePosition() const;
    int getRouterPosition() const;
    const IPAddress& getDestinationIP() const;      // Returns a const reference to the destination terminal IP
    string toString() const;                        // Returns a string with the packet1 cPagePosition
    bool operator==(const Packet&) const;           // Compares two packets
};