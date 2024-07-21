/**
 * @class Terminal
 * @brief Represents a computer with an IP address. It tracks the number of pages sent and received,
 *        and can send and receive pages through a connected router.
 */
#pragma once

#include "Page.hpp"

class Router;                               // Forward declaration

class Terminal {
private:
    const IPAddress ip;                   /**< IP address of the terminal */
    int receivedPages = 0;                /**< Number of total received pages */
    int sentPages = 0;                    /**< Number of total sent pages */
    int idForPage = 0;                    /**< ID for the next page to be sent */
    Router* connectedRouter;              /**< Pointer to the router connected to the terminal */
public:
    /**
     * @brief Constructs a Terminal object with a specified IP address and a connection to a router.
     * @param ip The IP address of the terminal.
     * @param router Pointer to the router the terminal is connected to.
     */
    Terminal(IPAddress ip, Router *router);
    /**
     * @brief Default Destructor
     */
    ~Terminal();
    /**
     * @brief Sends a page with specified length to a destination IP through the connected router.
     * @param length The length of the page to be sent.
     * @param destIP The destination IP address for the page.
     */
    void sendPage(int length, IPAddress &destIP);
    /**
     * @brief Receives a page from a router, iterates through its nodes deleting each packet,
     *        then deletes the page, and increments the count of received pages.
     * @param page Pointer to the page being received.
     */
    void receivePage(Page *page);
    /**
     * @brief Retrieves the total number of pages received by the terminal.
     * @return Integer with the number of received pages.
     */
    int getReceivedPages() const;
    /**
     * @brief Retrieves the total number of pages sent by the terminal.
     * @return Integer with the number of sent pages.
     */
    int getSentPages() const;
    /**
     * @brief Retrieves the IP address of the terminal.
     * @return A constant reference to the terminal's IP address.
     */
    const IPAddress& getTerminalIp();
    /**
     * @brief Generates a string representation of the terminal, including its IP address.
     * @return A string representation of the terminal
     */
    string toString() const;

    friend class TerminalTest;      // Friend class for testing purposes
};