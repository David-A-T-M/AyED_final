#pragma once
/*
#include <vector>
#include "Packet.hpp"
#include "List.hpp"
#include "IPAddress.hpp"

using namespace std;

class Page : public List<Packet>{
private:
    const int page_id;                    // Page ID originIP+numberOfPageSent
    const int page_length;                // Page length in packets
    const IPAddress& originIP;           // Terminal IP
    const IPAddress& destinationIP;      // Destination terminal IP
public:
    Page(int, int, IPAddress& ,IPAddress&);
    ~Page();
    int getPageID() const;
    int getPageLength() const;
    const IPAddress& getOriginIP() const;
    const IPAddress& getDestinationIP() const;
    void print() const;
};
*/