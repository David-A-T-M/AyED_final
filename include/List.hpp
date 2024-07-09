#pragma once

/*
#include <iostream>
#include "Node.hpp"

using namespace std;

template <typename T> class List {

private:

    Node<T>* head = nullptr;            // Beginning of list
    Node<T>* tail = nullptr;            // End of list
    int node_count = 0;                 // Number of Nodos in list

public:

    List();                             // Constructor
    ~List();                            // Destructor, deletes all nodes

    void pushFront(T&);                 // Adds a node to the beginning with the specified data
    void pushBack(T&);                  // Adds a node to the end of the list with the specified data
    void pushAt(T&, int);               // Add a node with specific data at a specific position
    void popFront();                    // Remove the first node
    void popBack();                     // Remove the last node
    void popAt(int);                    // Remove a node at a specific position
    void swapNodesAt(int, int);         // Swap the nodes at two specific positions
    T* getHeadData();                   // Get a pointer to the data of the first node
    T* getTailData();                   // Get a pointer to the data of the last node
    T* getDataAtNode(int);              // Get a pointer to the data of a node at a specific position
    const T* getDataAtNode(int) const;  // Overloaded const version
    int getPos(T&) const;               // Get the position of a node with specific data
    int getNodeCount() const;           // Get the number of nodes in the list
    bool isEmpty() const;               // Check if the list is empty
    bool contains(T&) const;            // Check if the list contains a node with specific data
    void printList() const;             // Print the data of all nodes in the list
};

template <class T>
List<T>::List() = default;

template <class T>
List<T>::~List() {
    while (head != nullptr) {
        Node<T>* temp = head;
        head = head->getNext();
        delete temp;
    }
}

template <typename T>
void List<T>::pushFront(T& data) {

    auto* new_head = new Node<T>(data, head); // New node with the specified data and points to the current head

    if (this->isEmpty()) {              // If the list is empty, the new node is also the last node
        head = new_head;
        tail = new_head;
    }
    else {                              // If the list is not empty, the new node is the new head
        head = new_head;
    }
    node_count++;                       // Increase the node count
}

template <typename T>
void List<T>::pushBack(T& data) {

    auto* new_tail = new Node<T>(data, nullptr); // New node with the specified data and no next node

    if (this->isEmpty()) {              // If the list is empty, the new node becomes the head
        head = new_tail;
    }
    else {
        tail->setNext(new_tail);     // If the list is not empty, the old tail points to the new node
    }

    tail = new_tail;                    // The new node is the new tail
    node_count++;                       // Increase the node count
}

template <typename T>
void List<T>::pushAt(T& data, int pos) {

    if (pos < 0 || pos > node_count) {  // validate the position
        cout << "Can't insert node, invalid position." << endl;
        return;
    }

    if (pos == 0) {                     // If the position is 0, calls pushFront
        this->pushFront(data);
        return;
    }

    if (pos == node_count) {            // If the position is the last one, calls pushBack
        this->pushBack(data);
        return;
    }

    Node<T>* aux_ptr_prev = head;       // Will point to the node before the position
    Node<T>* aux_ptr = head->getNext(); // Will point to the node at the position
    int curr_pos = 1;

    while (curr_pos != pos) {           // Traverse the list until the position is reached
        aux_ptr_prev = aux_ptr;
        aux_ptr = aux_ptr->getNext();
        curr_pos++;
    }

    auto* pushed_node = new Node<T>(data, aux_ptr);  // The node at the position becomes the next node of the new node
    aux_ptr_prev->setNext(pushed_node);   // The node before the position points to the new node

    node_count++;                       // Increase the node count
}

template <typename T>
void List<T>::popFront() {
    if (head == nullptr) {              // If the list is empty
        cout << "Can't delete anything, the list is empty." << endl;
        return;
    }

    Node<T>* old_head = head;

    if (this->getNodeCount() == 1) {    // If there is only one node the list becomes empty
        head = nullptr;
        tail = nullptr;
    }
    else {
        head = head->getNext();         // The second node becomes the head
    }

    delete old_head;                    // Delete the old head
    node_count--;                       // Decrease the node count
}

template <typename T>
void List<T>::popBack() {
    if (tail == nullptr) {              // If the list is empty
        cout << "Can't delete anything, the list is empty." << endl;
        return;
    }

    Node<T>* old_tail = tail;

    if (this->getNodeCount() == 1) {    // If there is only one node the list becomes empty
        head = nullptr;
        tail = nullptr;
    }
    else {
        Node<T>* aux_ptr = head;
        while (aux_ptr->getNext() != tail) {
            aux_ptr = aux_ptr->getNext();
        }

        aux_ptr->setNext(nullptr);   // The node before the last one becomes the last one
        tail = aux_ptr;                 // Also becomes the tail
    }

    delete old_tail;                    // Delete the old tail
    node_count--;                       // Decrease the node count
}

template <typename T>
void List<T>::popAt(int pos) {
    if (pos < 0 || pos >= node_count) { // Validate the position
        cout << "Can't delete node, invalid position." << endl;
        return;
    }

    if (pos == 0) {                     // If the position is 0, calls popFront
        this->popFront();
        return;
    }

    if (pos == (this->getNodeCount() - 1)) {    // If the position is the last one, calls popBack
        this->popBack();
        return;
    }

    Node<T>* aux_ptr_prev = head;       // Will point to the node before the position
    Node<T>* aux_ptr = head->getNext(); // Will point to the node to delete
    int curr_pos = 1;

    while (curr_pos != pos) {           // Traverse the list until the position is reached
        aux_ptr_prev = aux_ptr;
        aux_ptr = aux_ptr->getNext();
        curr_pos++;
    }

    aux_ptr_prev->setNext(aux_ptr->getNext());  // The node before the position points to the node after the position
    delete aux_ptr;                     // Delete the node at the position
    node_count--;                       // Decrease the node count
}

template <typename T>
void List<T>::swapNodesAt(int m, int n) {
    if (m < 0 || n < 0 || m >= node_count || n >= node_count) {     //validate the positions
        cout << "Invalid value." << endl;
        return;
    }

    if (m == n) {                       // If the positions are the same, there is nothing to do
        return;
    }

    Node<T>* nodeM = head;
    Node<T>* nodeN = head;

    for (int i = 0; i <= max(m, n); ++i) {      // Traverse the list to find the nodes at M and N
        if (i < m) {
            nodeM = nodeM->getNext();
        }
        if (i < n) {
            nodeN = nodeN->getNext();
        }
    }

    T temp = *(nodeM->getData());               // Swap the data of the nodes
    nodeM->setData(*(nodeN->getData()));
    nodeN->setData(temp);
}

template <typename T>
T* List<T>::getHeadData() {
    return head ? head->getData() : nullptr;
}

template <class T>
T* List<T>::getTailData() {
    return tail ? tail->getData() : nullptr;
}

template <typename T>
T* List<T>::getDataAtNode(int pos) {
    if (head == nullptr || pos < 0 || pos >= node_count)     // Return nullptr for invalid position or empty list
        return nullptr;

    if (pos == 0)                       // If the position is 0, call getHeadData
        return this->getHeadData();

    if (pos == node_count - 1)          // If the position is the last one, call getTailData
        return this->getTailData();

    Node<T>* aux_ptr = head->getNext();
    int curr_pos = 1;

    while (curr_pos != pos) {           // Traverse the list until the position is reached
        aux_ptr = aux_ptr->getNext();
        curr_pos++;
    }

    return aux_ptr->getData();
}

template<typename T>
const T *List<T>::getDataAtNode(int pos) const {
    return const_cast<List<T>*>(this)->getDataAtNode(pos);
}

template <typename T>
int List<T>::getPos(T& data) const{

    Node<T>* current = head;
    int pos = 0;

    while (current) {                   // Traverse the list until the node with the specified data is found
        if (*(current->getData()) == data)      //Needs to overload the == operator
            return pos;
        current = current->getNext();
        pos++;
    }

    return -1;                          // Return -1 if the data is not found
}

template <class T>
int List<T>::getNodeCount() const{
    return node_count;
}

template <class T>
bool List<T>::isEmpty() const{
    return node_count == 0;
}

template <typename T>
bool List<T>::contains(T& data) const{
    return getPos(data) != -1;
}

template <typename T>
void List<T>::printList() const{

    Node<T>* aux_ptr = head;

    while (aux_ptr) {                   // Traverse the list and print the data of each node while the pointer is not null
        if (aux_ptr->getData() != nullptr) {
            cout << *(aux_ptr->getData()) << endl; // Dereference the pointer to the data, needs to overload the << operator
        }
        aux_ptr = aux_ptr->getNext();
    }

    cout << "Fin de lista" << endl;
}

//TODO: Fix the printList method to work calling toString() method from the data class*/