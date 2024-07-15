/*
 * Adjacency Node class to be used in a linked list, stack or queue;
 * it contains a pointer to data, an int value and a pointer to the next node
 */
#pragma once

#include <string>

using namespace std;

template <typename T>
class AdjNode {
    private:
        T* data;
        AdjNode* next;
        int val = 0;
    public:
        using valType = T;

        AdjNode();                              // Default Constructor
        explicit AdjNode(T*);                   // Constructor with data
        AdjNode(T*, int);                       // Constructor with data and value
        AdjNode(T*, AdjNode*);                  // Constructor with data and next
        AdjNode(T*, AdjNode*, int);             // Constructor with data, next and value
        ~AdjNode();                             // Default Destructor
        void setData(T*);                       // Setter for data
        void setNext(AdjNode*);                 // Setter for next
        void setVal(int);                       // Setter for value
        T* getData() const;                     // Getter for data
        AdjNode<T>* getNext() const;            // Getter for next
        int getVal() const;                     // Getter for value
        bool hasNext();                         // Returns true if next points to another node
        bool operator==(const AdjNode<T>&) const;  // Overloaded == operator
        string toString() const;                // Returns a string representation of the data
};

template <typename T>
AdjNode<T>::AdjNode()
        : data(nullptr), next(nullptr) {}

template <typename T>
AdjNode<T>::AdjNode(T* data)
        : data(data), next(nullptr) {}

template <typename T>
AdjNode<T>::AdjNode(T* data, int a)
        : data(data), val(a) {}

template <typename T>
AdjNode<T>::AdjNode(T* data, AdjNode* next)
        : data(data), next(next) {}

template <typename T>
AdjNode<T>::AdjNode(T* data, AdjNode* next, int a)
        : data(data), next(next), val(a) {}

template <typename T>
AdjNode<T>::~AdjNode() = default;

template <typename T>
void AdjNode<T>::setData(T* newData) {
    this->data = newData;
}

template <typename T>
void AdjNode<T>::setNext(AdjNode* newNext) {
    this->next = newNext;
}

template <typename T>
void AdjNode<T>::setVal(int newA) {
    this->val = newA;
}

template<typename T>
T *AdjNode<T>::getData() const {
    return data;
}

template <typename T>
AdjNode<T>* AdjNode<T>::getNext() const {
    return next;
}

template <typename T>
int AdjNode<T>::getVal() const {
    return this->val;
}

template <typename T>
bool AdjNode<T>::hasNext() {
    return next != nullptr;
}

template<typename T>
bool AdjNode<T>::operator==(const AdjNode<T>& node) const {
    return *data == *node.getData();
}

template<typename T>
string AdjNode<T>::toString() const {
    return data->toString();
}