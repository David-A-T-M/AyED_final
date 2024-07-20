#include "Page.hpp"

Page::Page(int cPageID, int cPageLength, const IPAddress& rOriginIP, const IPAddress& rDestinationIP)
        : cPageID(cPageID), cPageLength(cPageLength), rOriginIP(rOriginIP), rDestinationIP(rDestinationIP) {
    for (int i = 0; i < cPageLength; i++){          // Instantiates a new packet for each position in the page.
        auto *new_packet = new Packet(cPageID, i, cPageLength, 0, rDestinationIP, rOriginIP);
        this->pushBack(new_packet);
    }
}

Page::Page(List<Node<Packet>> *packets)
        : cPageID(packets->getHeadData()->getPageID()),
          cPageLength(packets->getNodeCount()),
          rOriginIP(packets->getHeadData()->getOriginIP()),
          rDestinationIP(packets->getHeadData()->getDestinationIP()) {
    Packet *packet;
    for (int i = 0; i < packets->getNodeCount(); i++){      // Adds a node for each of the original packets.
        packet = packets->getDataAtNode(i);
        this->pushBack(packet);
    }
    delete packets;     // Deletes the original list of packets, but not the packets themselves.
}

Page::~Page() = default;

int Page::getPageID() const {
    return cPageID;
}

int Page::getPageLength() const {
    return cPageLength;
}

const IPAddress& Page::getOriginIP() const {
    return rOriginIP;
}

const IPAddress& Page::getDestinationIP() const {
    return rDestinationIP;
}

void Page::print() const {
    cout << "Page ID: " << cPageID << endl;
    for (int i = 0; i < cPageLength; i++) {
        cout << this->getDataAtNode(i)->toString() << endl;
    }
    cout << "Page length: " << cPageLength << endl;
    cout << endl;
}