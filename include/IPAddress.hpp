#pragma once

#include <iostream>
#include <bitset>
#include <cstdint>

using namespace std;

class IPAddress {
private:
    uint8_t modemIP;
    uint8_t terminalIP;
    bool Modem;

public:
    explicit IPAddress(uint8_t);
    IPAddress(uint8_t, uint8_t);
    ~IPAddress();
    uint8_t getModemIP() const;
    uint8_t getTerminalIP() const;
    bool isModem() const;
    string toString() const;
    bool operator==(const IPAddress& ip) const;
};