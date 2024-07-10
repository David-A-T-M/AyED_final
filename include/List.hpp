//
// Created by David on 06/07/2024.
//
#pragma once

#include <iostream>
#include "Node.hpp"

using namespace std;

template <typename T> class List {

private:
    Node<T> *pHead = nullptr;               // Beginning of list
    Node<T> *pTail = nullptr;               // End of list
    int nodeCount = 0;                      // Number of Nodos in list

protected:
    Node<T>* getHead() const;               // Get a pointer to the first node

public:
    List();                                 // Constructor
    ~List();                                // Destructor, deletes all nodes
    void pushFront(T*);                     // Adds a node to the beginning with the specified data
    void pushBack(T*);                      // Adds a node to the end of the list with the specified data
    void pushAt(T*, int);                   // Add a node with specific data at a specific position
    void popFront();                        // Remove the first node
    void popBack();                         // Remove the last node
    void popAt(int);                        // Remove a node at a specific position
    void swapNodesAt(int, int);             // Swap the nodes at two specific positions
    T* getHeadData() const;                 // Get a pointer to the data of the first node
    T* getTailData() const;                 // Get a pointer to the data of the last node
    T* getDataAtNode(int)const;             // Get a pointer to the data of a node at a specific position
    int getPos(T*) const;                   // Get the position of a node with specific data
    int getNodeCount() const;               // Get the number of nodes in the list
    bool isEmpty() const;                   // Check if the list is empty
    bool contains(T*) const;                // Check if the list contains a node with specific data
    virtual void printList() const;         // Print the data of all nodes in the list

    friend class ListTest;                  // For testing purposes
};

template <class T>
List<T>::List() = default;

template <class T>
List<T>::~List() {
    while (pHead != nullptr) {
        Node<T> *temp = pHead;
        pHead = pHead->getNext();
        delete temp;
    }
}

template <typename T>
Node<T>* List<T>::getHead() const {
    return pHead;
}

template <typename T>
void List<T>::pushFront(T *data) {

    auto *new_head = new Node<T>(data, pHead); // New node with the specified data and points to the current pHead

    if (this->isEmpty()) {                  // If the list is empty, the new node is also the last node
        pHead = new_head;
        pTail = new_head;
    }
    else {                                  // If the list is not empty, the new node is the new pHead
        pHead = new_head;
    }
    nodeCount++;                            // Increase the node count
}

template <typename T>
void List<T>::pushBack(T* data) {

    auto *new_tail = new Node<T>(data, nullptr); // New node with the specified data and no next node

    if (this->isEmpty()) {                  // If the list is empty, the new node becomes the pHead
        pHead = new_tail;
    }
    else {
        pTail->setNext(new_tail);   // If the list is not empty, the old pTail points to the new node
    }

    pTail = new_tail;                       // The new node is the new pTail
    nodeCount++;                            // Increase the node count
}

template <typename T>
void List<T>::pushAt(T *data, int pos) {

    if (pos < 0 || pos > nodeCount) {       // validate the position
        cout << "Can't insert node, invalid position." << endl;
        return;
    }

    if (pos == 0) {                         // If the position is 0, calls pushFront
        this->pushFront(data);
        return;
    }

    if (pos == nodeCount) {                 // If the position is the last one, calls pushBack
        this->pushBack(data);
        return;
    }

    Node<T> *aux_prev = pHead;              // Will point to the node before the position
    Node<T> *aux = pHead->getNext();        // Will point to the node at the position
    int curr_pos = 1;

    while (curr_pos != pos) {               // Traverse the list until the position is reached
        aux_prev = aux;
        aux = aux->getNext();
        curr_pos++;
    }

    auto* new_node_at = new Node<T>(data, aux);  // The node at the position becomes the next node of the new node
    aux_prev->setNext(new_node_at); // The node before the position points to the new node

    nodeCount++;                            // Increase the node count
}

template <typename T>
void List<T>::popFront() {
    if (pHead == nullptr) {                 // If the list is empty
        cout << "Can't delete anything, the list is empty." << endl;
        return;
    }

    Node<T>* old_head = pHead;

    if (this->getNodeCount() == 1) {        // If there is only one node the list becomes empty
        pHead = nullptr;
        pTail = nullptr;
    }
    else {
        pHead = pHead->getNext();           // The second node becomes the pHead
    }

    delete old_head;                        // Delete the old pHead
    nodeCount--;                            // Decrease the node count
}

template <typename T>
void List<T>::popBack() {
    if (pTail == nullptr) {                 // If the list is empty
        cout << "Can't delete anything, the list is empty." << endl;
        return;
    }

    Node<T>* old_tail = pTail;

    if (this->getNodeCount() == 1) {        // If there is only one node the list becomes empty
        pHead = nullptr;
        pTail = nullptr;
    }
    else {
        Node<T>* aux = pHead;
        while (aux->getNext() != pTail) {
            aux = aux->getNext();
        }

        aux->setNext(nullptr);     // The node before the last one becomes the last one
        pTail = aux;                        // Also becomes the pTail
    }

    delete old_tail;                        // Delete the old pTail
    nodeCount--;                            // Decrease the node count
}

template <typename T>
void List<T>::popAt(int pos) {
    if (pos < 0 || pos >= nodeCount) {      // Validate the position
        cout << "Can't delete node, invalid position." << endl;
        return;
    }

    if (pos == 0) {                         // If the position is 0, calls popFront
        this->popFront();
        return;
    }

    if (pos == (this->getNodeCount() - 1)) {// If the position is the last one, calls popBack
        this->popBack();
        return;
    }

    Node<T>* aux_prev = pHead;              // Will point to the node before the position
    Node<T>* aux = pHead->getNext();        // Will point to the node to delete
    int curr_pos = 1;

    while (curr_pos != pos) {               // Traverse the list until the position is reached
        aux_prev = aux;
        aux = aux->getNext();
        curr_pos++;
    }

    aux_prev->setNext(aux->getNext());  // The node before the position points to the node after the position
    delete aux;                             // Delete the node at the position
    nodeCount--;                            // Decrease the node count
}

template <typename T>
void List<T>::swapNodesAt(int m, int n) {
    if (m < 0 || n < 0 || m >= nodeCount || n >= nodeCount) {     //validate the positions
        cout << "Invalid value." << endl;
        return;
    }

    if (m == n) {                           // If the positions are the same, there is nothing to do
        return;
    }

    Node<T> *node_m = pHead;
    Node<T> *node_n = pHead;

    for (int i = 0; i <= max(m, n); ++i) {  // Traverse the list to find the nodes at M and N
        if (i < m) {
            node_m = node_m->getNext();
        }
        if (i < n) {
            node_n = node_n->getNext();
        }
    }

    T *temp = node_m->getData();            // Swap the data of the nodes
    node_m->setData(node_n->getData());
    node_n->setData(temp);
}

template <typename T>
T* List<T>::getHeadData() const {
    return pHead ? pHead->getData() : nullptr;
}

template <class T>
T* List<T>::getTailData() const {
    return pTail ? pTail->getData() : nullptr;
}

template <typename T>
T* List<T>::getDataAtNode(int pos) const {
    if (pHead == nullptr || pos < 0 || pos >= nodeCount)    // Return nullptr for invalid position or empty list
        return nullptr;

    if (pos == 0)                           // If the position is 0, call getHeadData
        return this->getHeadData();

    if (pos == nodeCount - 1)               // If the position is the last one, call getTailData
        return this->getTailData();

    Node<T> *aux = pHead->getNext();
    int curr_pos = 1;

    while (curr_pos != pos) {               // Traverse the list until the position is reached
        aux = aux->getNext();
        curr_pos++;
    }

    return aux->getData();
}

template <typename T>
int List<T>::getPos(T* data) const{

    Node<T> *current = pHead;
    int pos = 0;

    while (current) {                       // Traverse the list until the node with the specified data is found
        if (*current->getData() == *data)   //Needs to overload the == operator
            return pos;
        current = current->getNext();
        pos++;
    }

    return -1;                              // Return -1 if the data is not found
}

template <class T>
int List<T>::getNodeCount() const{
    return nodeCount;
}

template <class T>
bool List<T>::isEmpty() const{
    return nodeCount == 0;
}

template <typename T>
bool List<T>::contains(T* data) const{
    return getPos(data) != -1;
}

template <typename T>
void List<T>::printList() const{
    cout << "Start of list" << endl;
    Node<T> *aux = pHead;

    while (aux) {                           // Traverse the list and print the data of each node while the pointer is not null
        if (aux->getData() != nullptr) {
            cout << aux->getData()->toString() << endl; // Dereference the pointer to the data, needs to overload the << operator
        }
        aux = aux->getNext();
    }

    cout << "End of list" << endl;
}