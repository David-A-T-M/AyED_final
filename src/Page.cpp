//
// Created by david on 13/05/24.
//
#include "../include/Page.hpp"

Page::Page(int cPageID, int cPageLength, const IPAddress& rOriginIP, const IPAddress& rDestinationIP)
        : cPageID(cPageID), cPageLength(cPageLength), rOriginIP(rOriginIP), rDestinationIP(rDestinationIP) {
    for (int i = 0; i < cPageLength; i++){
        auto *new_packet =new Packet(cPageID, i, 0, rDestinationIP);
        this->pushBack(new_packet);
    }
}

Page::~Page() = default;

int Page::getPageID() const {
    return cPageID;
}

int Page::getPageLength() const {
    return cPageLength;
}

const IPAddress& Page::getOriginIP() const{
    return rOriginIP;
}

const IPAddress& Page::getDestinationIP() const{
    return rDestinationIP;
}

void Page::print() const {
    cout << "Page ID: " << cPageID << endl;
    for (int i = 0; i < cPageLength; i++){
        cout << this->getDataAtNode(i)->toString() << endl;
    }
    cout << "Page length: " << cPageLength << endl;
    cout << endl;
}