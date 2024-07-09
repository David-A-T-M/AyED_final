#pragma once

using namespace std;

template <class T> class Node {
private:
    T* data;
    Node* next;
public:
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

template <class T>
Node<T>::Node()
        : data(nullptr), next(nullptr) {}

template <class T>
Node<T>::Node(T* data)
        : data(data), next(nullptr) {}

template <class T>
Node<T>::Node(T* data, Node* next)
        : data(data), next(next) {}

template <class T>
Node<T>::~Node(){
    delete data;
}

template <class T>
void Node<T>::setData(T* newData) {
    this->data = newData;
}

template <class T>
void Node<T>::setNext(Node* newNext) {
    this->next = newNext;
}

template<class T>
T *Node<T>::getData() const {
    return data;
}

template <class T>
Node<T>* Node<T>::getNext() const {
    return next;
}

template <class T>
bool Node<T>::hasNext() {
    return next != nullptr;
}

template<class T>
bool Node<T>::operator==(const Node<T>& node) const {
    return *data == *node.getData();
}

template<class T>
string Node<T>::toString() const {
    return data->toString();
}

