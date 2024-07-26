#include "..\include\IPAddress.hpp"

IPAddress::IPAddress() : routerIP(0), terminalIP(0), Router(true) {}

IPAddress::IPAddress(uint8_t routerIP)
            : routerIP(routerIP), terminalIP(0), Router(true) {}

IPAddress::IPAddress(uint8_t routerIP, uint8_t terminalIP)
            : routerIP(routerIP), terminalIP(terminalIP), Router(false) {}

IPAddress::~IPAddress() = default;

uint8_t IPAddress::getRouterIP() const {
    return routerIP;
}

uint8_t IPAddress::getTerminalIP() const {
    return terminalIP;
}

bool IPAddress::isRouter() const {
    return Router;
}

string IPAddress::toString() const {
    if (Router) {
        return "Router IP: " + bitset<8>(routerIP).to_string();
    } else {
        return "Terminal IP: " + bitset<8>(routerIP).to_string() + "." + bitset<8>(terminalIP).to_string();
    }
}

bool IPAddress::operator==(const IPAddress &ip) const {
    return routerIP == ip.routerIP && terminalIP == ip.terminalIP;
}