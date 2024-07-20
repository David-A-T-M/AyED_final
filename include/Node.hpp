#pragma once

#include <string>

using namespace std;

/**
 * @class Node
 * @brief Node class to be used in a linked list, stack or queue.
 *        Stores a pointer to the data and a pointer to the next node in the structure.
 * @tparam T Type of the data to be stored in the node.
 */
template <typename T>
class Node {
private:
    T* data;                /**< Pointer to the data stored in the node. */
    Node* next;             /**< Pointer to the next node in the structure. */
public:
    using valType = T;

    /**
     * @brief Default Constructor. Initializes a new instance of the Node class with *data and *next set to nullptr.
     */
    Node();
    /**
     * @brief Data Constructor. Initializes a new instance of the Node class with the provided data and a null next pointer.
     * @param data Pointer to the data to be stored in the node.
     */
    explicit Node(T *data);
    /**
     * @brief Data Next Constructor. Initializes a new instance of the Node class with the provided data and next node.
     * @param data Pointer to the data to be stored in the node.
     * @param next Pointer to the next node in the structure.
     */
    Node(T *data, Node *next);
    /**
     * @brief Default Destructor.
     */
    ~Node();
    /**
     * @brief Sets the data of the node.
     * @param newData Pointer to the new data for the node.
     */
    void setData(T *newData);
    /**
     * @brief Sets the next node in the structure.
     * @param newNext Pointer to the new next node.
     */
    void setNext(Node *newNext);
    /**
     * @brief Gets a pointer to the data of the node.
     * @return Node's data.
     */
    T* getData() const;
    /**
     * @brief Gets the next node in the structure.
     * @return Next node.
     */
    Node<T>* getNext() const;
    /**
     * @brief Checks if there is a next node.
     * @return True if there is a next node, false otherwise.
     */
    bool hasNext();
    /**
     * @brief Compares the data of two nodes.
     * @param node Node to compare data with.
     * @return True if the data are equal, false otherwise.
     */
    bool operator==(const Node<T> &node) const;
    /**
     * @brief Returns a string representation of the node's data.
     * @return String representing the node's data.
     */
    string toString() const;
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

