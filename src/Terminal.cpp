//
// Created by david on 13/05/24.
//
#include "Terminal.hpp"
#include "Router.hpp"

Terminal::Terminal(IPAddress ip, Router* router)
        : ip(ip), connectedRouter(router) {
    idForPage = ip.getTerminalIP()*1000;
}

Terminal::~Terminal() = default;

void Terminal::sendPage(int pageLength, IPAddress& destIP) {
    Page *page = new Page(idForPage, pageLength, ip, destIP);
    //connectedRouter->receivePage(page); TODO
    sentPages++;
}

void Terminal::receivePage(Page *page) {
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
    return "holi, soy una terminal";
    //TODO
}