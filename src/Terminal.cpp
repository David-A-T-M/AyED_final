//
// Created by david on 13/05/24.
//
#include "Terminal.hpp"
#include "Router.hpp"

Terminal::Terminal(IPAddress ip, Router* router)
        : ip(ip), connectedRouter(router) {
    idForPage = ip.getRouterIP()*1000000+ip.getTerminalIP()*1000;
}

Terminal::~Terminal() = default;

void Terminal::sendPage(int pageLength, const IPAddress& destIP) {
    Page *page = new Page(idForPage, pageLength, ip, destIP);
    connectedRouter->receivePage(page);
    sentPages++;
    idForPage++;
}

void Terminal::receivePage(Page *page) {
    for (int i = 0; i < page->getNodeCount(); i++) {
        delete page->getDataAtNode(i);
    }
    delete page;
    receivedPages++;
}

int Terminal::getReceivedPages() const {
    return receivedPages;
}

int Terminal::getSentPages() const {
    return sentPages;
}

const IPAddress& Terminal::getTerminalIp() {
    return ip;
}

string Terminal::toString() const {
    string a;
    a += ip.toString();
    a += "\tRP: " + to_string(receivedPages) + "\tSP: " + to_string(sentPages);
    return a;
}