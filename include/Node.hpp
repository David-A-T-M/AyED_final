/*
 * Node class to be used in a linked list, stack or queue;
 * it contains a pointer to data and a pointer to the next node
 */
#pragma once

#include <string>

using namespace std;

template <typename T>
class Node {
private:
    T* data;
    Node* next;
public:
    using valType = T;

    Node();                                 // Default Constructor
    explicit Node(T*);                      // Data Constructor
    Node(T*, Node*);                        // Data Next Constructor
    ~Node();                                // Destructor, deletes data
    void setData(T*);                       // Setter for data
    void setNext(Node*);                    // Setter for next
    T* getData() const;                     // Getter for data
    Node<T>* getNext() const;               // Getter for next
    bool hasNext();                         // Returns true if next points to another node
    bool operator==(const Node<T>&) const;  // Overloaded == operator
    string toString() const;                // Returns a string representation of the data
};

template <typename T>
Node<T>::Node()
        : data(nullptr), next(nullptr) {}

template <typename T>
Node<T>::Node(T* data)
        : data(data), next(nullptr) {}

template <typename T>
Node<T>::Node(T* data, Node* next)
        : data(data), next(next) {}

template <typename T>
Node<T>::~Node() = default;

template <typename T>
void Node<T>::setData(T* newData) {
    this->data = newData;
}

template <typename T>
void Node<T>::setNext(Node* newNext) {
    this->next = newNext;
}

template<typename T>
T *Node<T>::getData() const {
    return data;
}

template <typename T>
Node<T>* Node<T>::getNext() const {
    return next;
}

template <typename T>
bool Node<T>::hasNext() {
    return next != nullptr;
}

template<typename T>
bool Node<T>::operator==(const Node<T>& node) const {
    return *data == *node.getData();
}

template<typename T>
string Node<T>::toString() const {
    return data->toString();
}

