//
// Created by David on 08/07/2024.
//
#include "../include/Packet.hpp"

Packet::Packet(int pageID, int pagePosition, int routerPosition, const IPAddress& destinationIP)
        : cPageID(pageID), cPagePosition(pagePosition), routerPosition(routerPosition), rDestinationIP(destinationIP) {}

Packet::~Packet() = default;

int Packet::getPageID() const {
    return cPageID;
}

int Packet::getPagePosition() const {
    return cPagePosition;
}

int Packet::getRouterPosition() const {
    return routerPosition;
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
