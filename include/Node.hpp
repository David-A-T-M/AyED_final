#pragma once

using namespace std;

template <class T> class Node {
private:
    T data;
    Node* next;
public:
    Node();
    explicit Node(T);
    Node(T, Node*);
    ~Node();
    void setData(T&);
    void setNext(Node*);
    T* getData();
    Node<T>* getNext();
    bool hasNext();
    bool operator==(T&) const;
    string toString() const;
};

template <class T>
Node<T>::Node() : data(), next(nullptr) {
}

template <class T>
Node<T>::Node(T data) :Node(data, nullptr) {
}

template <class T>
Node<T>::Node(T data, Node* next) : data(data), next(next) {
}

template <class T>
Node<T>::~Node(){
    delete data;
}

template <class T>
void Node<T>::setData(T& newData) {
    this->data = newData;
}

template <class T>
void Node<T>::setNext(Node* n) {
    this->next = n;
}

template <class T>
T* Node<T>::getData() {
    return &data;
}

template <class T>
Node<T>* Node<T>::getNext() {
    return next;
}

template <class T>
bool Node<T>::hasNext() {
    return next != nullptr;
}

template<class T>
bool Node<T>::operator==(T& someT) const {
    return data == someT;
}

template<class T>
string Node<T>::toString() const {
    return data.toString();
}

