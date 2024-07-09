#include "../include/IPAddress.hpp"

IPAddress::IPAddress(uint8_t modemIP)
            : modemIP(modemIP), terminalIP(0), Modem(true) {}

IPAddress::IPAddress(uint8_t modemIP, uint8_t terminalIP)
            : modemIP(modemIP), terminalIP(terminalIP), Modem(false) {}

IPAddress::~IPAddress() = default;

uint8_t IPAddress::getModemIP() const{
    return modemIP;
}

uint8_t IPAddress::getTerminalIP() const{
    return terminalIP;
}

bool IPAddress::isModem() const{
    return Modem;
}

string IPAddress::toString() const{
    if (Modem) {
        return "Modem IP: " + bitset<8>(modemIP).to_string();
    } else {
        return "Terminal IP: " + bitset<8>(modemIP).to_string() + "." + bitset<8>(terminalIP).to_string();
    }
}

bool IPAddress::operator==(const IPAddress &ip) const{
    return modemIP == ip.modemIP && terminalIP == ip.terminalIP;
}

