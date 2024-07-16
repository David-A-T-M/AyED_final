/**
 * @class AdjNode
 * @brief Adjacent Node class to be used in a linked list, stack or queue.
 *        Stores a pointer to the data, an integer value and a pointer to the next node in the structure.
 * @tparam T Type of the data to be stored in the node.
 */
#pragma once

#include <string>

using namespace std;

template <typename T>
class AdjNode {
private:
    T* data;                    /**< Pointer to the data stored in the node. */
    AdjNode* next;              /**< Pointer to the next node in the structure. */
    int val = 0;                /**< Integer stored in the node. */
public:
    using valType = T;

    /**
     * @brief Default Constructor. Initializes a new instance of the Node class with *data and *next set to nullptr.
     */
    AdjNode();
    /**
     * @brief Data Constructor. Initializes a new instance of the Node class with the provided data and a null next pointer.
     * @param data Pointer to the data to be stored in the node.
     */
    explicit AdjNode(T *data);
    /**
     * @brief Data Next Constructor. Initializes a new instance of the Node class with the provided data and int value.
     *        Sets *next to nullptr.
     * @param data Pointer to the data to be stored in the node.
     * @param a Integer value to be stored in the node.
     */
    AdjNode(T *data, int a);
    /**
     * @brief Data Next Constructor. Initializes a new instance of the Node class with the provided data and next node.
     * @param data Pointer to the data to be stored in the node.
     * @param next Pointer to the next node in the structure.
     */
    AdjNode(T *data, AdjNode *next);
    /**
     * @brief Data Next Constructor. Initializes a new instance of the Node class with the provided data, int value and next node.
     * @param data Pointer to the data to be stored in the node.
     * @param next Pointer to the next node in the structure.
     * @param a Integer value to be stored in the node.
     */
    AdjNode(T *data, AdjNode *next, int a);
    /**
     * @brief Default Destructor.
     */
    ~AdjNode();
    /**
     * @brief Sets the data of the node.
     * @param newData Pointer to the new data for the node.
     */
    void setData(T *newData);
    /**
     * @brief Sets the next node in the structure.
     * @param newNext Pointer to the new next node.
     */
    void setNext(AdjNode *newNext);
    /**
     * @brief Sets the integer value of the node.
     * @param newA Integer value to be stored in the node.
     */
    void setVal(int newA);
    /**
     * @brief Gets the data stored in the node.
     * @return Pointer to the node's data.
     */
    T* getData() const;
    /**
     * @brief Gets the next node in the structure.
     * @return Pointer to the next node.
     */
    AdjNode<T>* getNext() const;
    /**
     * @brief Gets the integer value stored in the node.
     * @return Integer value stored in the node.
     */
    int getVal() const;
    /**
     * @brief Checks if there is a next node.
     * @return True if there is a next node, false otherwise.
     */
    bool hasNext();
    /**
     * @brief Compares the data and integer value of two nodes.
     * @param node Node to compare data and integer value with.
     * @return True if the data and integer value are equal, false otherwise.
     */
    bool operator==(const AdjNode<T>&) const;
    /**
     * @brief Returns a string representation of the node's data.
     * @return String representing the node's data.
     */
    string toString() const;
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
    return (*data == *node.getData() && val == node.getVal());
}

template<typename T>
string AdjNode<T>::toString() const {
    return data->toString();
}