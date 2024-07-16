//
// Created by David on 08/07/2024.
//
#include "Packet.hpp"

Packet::Packet(int pageID, int pagePosition, int routerPriority, const IPAddress &destinationIP)
        : cPageID(pageID), cPagePosition(pagePosition), routerPriority(routerPriority), rDestinationIP(destinationIP) {}

Packet::~Packet() = default;

int Packet::getPageID() const {
    return cPageID;
}

int Packet::getPagePosition() const {
    return cPagePosition;
}

int Packet::getRouterPriority() const {
    return routerPriority;
}

const IPAddress& Packet::getDestinationIP() const {
    return rDestinationIP;
}

string Packet::toString() const {
    return "Packet " + to_string(cPagePosition);
}

bool Packet::operator==(const Packet& packet) const {
    return cPageID == packet.cPageID && cPagePosition == packet.cPagePosition;
}
