/*
 * Class terminal that represents a computer, it has an IP, a number of received and sent pages,
 * an ID for the pages (IP*1000+idForPage), and a pointer to the router where it is connected.
 */
#pragma once

#include "Page.hpp"

class Router;                               // Forward declaration

class Terminal {
private:
    const IPAddress ip;                     // IP of the terminal, routerIP + terminal nº
    int receivedPages = 0;                  // Number of total received pages
    int sentPages = 0;                      // Number of total sent pages
    int idForPage = 0;                      // ID for the pages
    Router* connectedRouter;                // Pointer to the router connected to the terminal
public:
    Terminal(IPAddress, Router*);           // Constructor, receives the ip and the pointer from the router
    ~Terminal();                            // Destructor
    void sendPage(int, IPAddress&);         // Receives length and dest from router, and calls it to receive the page
    void receivePage(Page*);                // Receives a page from a router, deletes it and increments receivedPages
    int getReceivedPages() const;           // Returns the number of received pages
    int getSentPages() const;               // Returns the number of sent pages
    const IPAddress& getTerminalIp();       // Returns a const reference to the terminal IP
    string toString() const;                // Returns a string with the terminal IP

    friend class TerminalTest;              // Friend class for testing
};