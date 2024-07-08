#include "../include/Packet.hpp"

Packet::Packet(int pageID, int pagePosition, int routerPosition, IPAddress& destinationIP)
        : pageID(pageID), pagePosition(pagePosition), routerPosition(routerPosition), destinationIP(destinationIP) {}

Packet::~Packet() = default;

int Packet::getPageID() const {
    return pageID;
}

int Packet::getPagePosition() const {
    return pagePosition;
}

int Packet::getRouterPosition() const {
    return routerPosition;
}

const IPAddress& Packet::getDestinationIP() const {
    return destinationIP;
}

string Packet::toString() const {
    return "Packet " + to_string(pagePosition);
}

bool Packet::operator==(const Packet& someP) const {
    return pageID == someP.pageID && pagePosition == someP.pagePosition;
}
