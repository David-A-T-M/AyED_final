//
// Created by David on 06/07/2024.
//
#pragma once

#include "Packet.hpp"
#include "List.hpp"
#include "Node.hpp"

using namespace std;

class Page : public List<Node<Packet>>{
private:
    const int cPageID;                      // Page ID originIP+numberOfPageSent
    const int cPageLength;                  // Page length in packets
    const IPAddress& rOriginIP;             // Terminal IP
    const IPAddress& rDestinationIP;        // Destination terminal IP
public:
    Page(int, int, const IPAddress&, const IPAddress&);
    ~Page();
    int getPageID() const;
    int getPageLength() const;
    const IPAddress& getOriginIP() const;
    const IPAddress& getDestinationIP() const;
    void print() const;
};