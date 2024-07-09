//
// Created by david on 13/05/24.
//
#include "../include/Page.hpp"
/*
Page::Page(int page_id, int page_length, IPAddress& originIP, IPAddress& destinationIP)
        : page_id(page_id), page_length(page_length), originIP(originIP), destinationIP(destinationIP){
    for (int i = 0; i < page_length; i++){
        Packet packet(page_id, i, 0, destinationIP);
        this->pushBack(packet);
    }
}

Page::~Page() = default;

int Page::getPageID() const {
    return page_id;
}

int Page::getPageLength() const {
    return page_length;
}

const IPAddress& Page::getOriginIP() const{
    return originIP;
}

const IPAddress& Page::getDestinationIP() const{
    return destinationIP;
}

void Page::print() const {
    cout << "Page ID: " << page_id << endl;
    for (int i = 0; i < page_length; i++){
        cout << this->List::getDataAtNode(i)->toString() << endl;
    }
    cout << "Page length: " << page_length << endl;
    cout << endl;
}


*/