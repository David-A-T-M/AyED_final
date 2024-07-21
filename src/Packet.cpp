#include "Packet.hpp"

Packet::Packet(int pageID, int pagePosition, int pageLength, int routerPriority, const IPAddress &destinationIP, const IPAddress &originIP)
        : cPageID(pageID),
          cPagePosition(pagePosition),
          routerPriority(routerPriority),
          rDestinationIP(destinationIP),
          rOriginIP(originIP),
          cPageLength(pageLength) {}

Packet::~Packet() = default;

void Packet::setRouterPriority(int routPri) {
    routerPriority = routPri;
}

int Packet::getPageID() const {
    return cPageID;
}

int Packet::getPagePosition() const {
    return cPagePosition;
}

int Packet::getPageLength() const {
    return cPageLength;
}

int Packet::getRouterPriority() const {
    return routerPriority;
}

const IPAddress& Packet::getDestinationIP() const {
    return rDestinationIP;
}

const IPAddress& Packet::getOriginIP() const {
    return rOriginIP;
}

string Packet::toString() const {
    return to_string(cPageID) + "-" + to_string(cPagePosition);
}

bool Packet::operator==(const Packet& packet) const {
    return cPageID == packet.cPageID && cPagePosition == packet.cPagePosition;
}