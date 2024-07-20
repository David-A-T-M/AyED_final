#pragma once

#include <iostream>

using namespace std;

/**
 * @class List
 * @brief Composed of generic nodes (NodeT) that store at least a pointer to the data of the type that the node can store.
 *        This class provides a flexible structure for a singly linked list, allowing for common list operations such as
 *        insertion at the beginning, end, and at a specific position within the list, as well as removal of nodes and
 *        retrieval of data. It supports operations to check the list's emptiness, count the nodes, and search for data
 *        within the list. The class is designed to be used with any data type that can be pointed to by the nodes.
 * @class NodeT The type of the nodes that compose the list.
 */
template <typename NodeT>
class List {

private:
    NodeT *pHead;     /**< Pointer to the first node in the list */
    NodeT *pTail;     /**< Pointer to the last node in the list */
    int nodeCount;    /**< Number of nodes in the list */

public:
    /**
     * @brief Default constructor
     */
    List();
    /**
     * @brief Destructor for the List class.
     *        Iterates through the list and deletes each node to free up memory.
     *        Does not delete the data pointed to by the nodes.
     */
    ~List();
    /**
     * @brief Adds a node with the specified data at the beginning of the list.
     *        The data type must match the type that NodeT can store.
     * @param data pointer to the data of the type that can be stored in the new node
     */
    void pushFront(typename NodeT::valType *data);
    /**
     * @brief Adds a node with the specified data at the end of the list.
     *        The data type must match the type that NodeT can store.
     * @param data Pointer to the data to be stored in the new node
     */
    void pushBack(typename NodeT::valType *data);
    /**
     * @brief Adds a node with the specified data at the given position. The existing node at this position
     *        and all subsequent nodes are shifted one position to the end of the list.
     *        The data type must match the type that NodeT can store.
     * @param data  Pointer to the data to be stored in the new node.
     * @param pos   The position at which the new node will be inserted.
     */
    void pushAt(typename NodeT::valType *data, int pos);
    /**
     * @brief Removes the first node from the list. If the list is empty, it prints a message and does nothing.
     *        The NodeT object is deleted, but the data pointed to by the node is not deleted.
     */
    void popFront();
    /**
     * @brief Removes the last node from the list. If the list is empty, it prints a message and does nothing.
     *        The NodeT object is deleted, but the data pointed to by the node is not deleted.
     */
    void popBack();
    /**
     * @brief Removes a node at the specified position from the list. The nodes after the removed node
     *        are shifted one position to the beginning of the list. If the position is invalid or the list is empty,
     *        it prints a message and does nothing. The NodeT object at the position is deleted, but the data pointed
     *        by the node is not deleted.
     * @param pos The position of the node to be removed.
     */
    void popAt(int);
    /**
     * @brief Sets the data of the node at the specified position. If the position is invalid or the list is empty,
     *        does nothing.
     * @param pos The position of the node.
     * @param newData Pointer to the new data to be set.
     */
    void setDataAtNode(int pos, typename NodeT::valType *newData);
    /**
     * @brief Swaps the data of two nodes at the specified positions. If either position is invalid, it prints a message
     *        and does nothing. If the positions are the same, it does nothing.
     * @param m The position of the first node to swap.
     * @param n The position of the second node to swap.
     */
    void swapNodesAt(int m, int n);
    /**
     * @brief Gets a pointer to the first node in the list. If the list is empty, gets nullptr.
     * @return The first node.
     */
    NodeT* getHead() const;
    /**
     * @brief Gets a pointer to the last node in the list. If the list is empty, gets nullptr.
     * @return The last node.
     */
    NodeT* getTail() const;
    /**
     * @brief Gets a pointer to the node at the specified position. If the position is invalid or the list is empty,
     *        gets nullptr.
     * @param pos The position of the node.
     * @return The node at the specified position.
     */
    NodeT* getNode(int pos) const;
    /**
     * @brief Returns a pointer to the data of the first node in the list. If the list is empty, returns nullptr.
     * @return The data of the first node.
     */
    typename NodeT::valType* getHeadData() const;
    /**
     * @brief Returns a pointer to the data of the last node in the list. If the list is empty, returns nullptr.
     * @return The data of the last node.
     */
    typename NodeT::valType* getTailData() const;
    /**
     * @brief Returns a pointer to the data of the node at the specified position. If the position is invalid
     *        or the list is empty, returns nullptr.
     * @param pos The position of the node.
     * @return The data of the node at the specified position.
     */
    typename NodeT::valType* getDataAtNode(int pos)const;
    /**
     * @brief Returns the position of the first node that contains the specified data. If the data is not found, returns -1.
     * @param data Pointer to the data to search for.
     * @return The position of the node, or -1 if not found.
     */
    int getPos(typename NodeT::valType *data) const;
    /**
     * @brief Returns the number of nodes in the list.
     * @return The number of nodes.
     */
    int getNodeCount() const;
    /**
     * @brief Checks if the list is empty.
     * @return True if the list is empty, false otherwise.
     */
    bool isEmpty() const;
    /**
     * @brief Checks if the list contains a node with the specified data.
     * @param data Pointer to the data to search for.
     * @return bool True if the data is found, false otherwise.
     */
    bool contains(typename NodeT::valType *data) const;
    /**
     * @brief Prints the data of all nodes in the list to the standard output.
     */
    virtual void printList() const;
    /**
     * @brief Returns a string representation of the list, containing the data of all nodes.
     * @return string A string representation of the list.
     */
    virtual string toString() const;
};

template <typename NodeT>
List<NodeT>::List()
    : pHead(nullptr),
      pTail(nullptr),
      nodeCount(0) {}

template <typename NodeT>
List<NodeT>::~List() {
    while (pHead != nullptr) {
        NodeT *temp = pHead;
        pHead = pHead->getNext();
        delete temp;
    }
}

template <typename NodeT>
void List<NodeT>::pushFront(typename NodeT::valType* data) {

    auto *new_head = new NodeT(data, pHead);

    if (this->isEmpty()) {                  // If the list is empty, the new node is also the last node.
        pHead = new_head;
        pTail = new_head;
    }
    else {                                  // If the list is not empty, pHead points to the new node.
        pHead = new_head;
    }
    nodeCount++;                            // Increase the node count.
}

template <typename NodeT>
void List<NodeT>::pushBack(typename NodeT::valType* data) {

    auto *new_tail = new NodeT(data, nullptr);

    if (this->isEmpty()) {                  // If the list is empty, the new node is also the first node.
        pHead = new_tail;
    }
    else {
        pTail->setNext(new_tail);           // If the list is not empty, the old pTail points to the new node
    }

    pTail = new_tail;                       // The new node is now pTail
    nodeCount++;                            // Increase the node count
}

template <typename NodeT>
void List<NodeT>::pushAt(typename NodeT::valType* data, int pos) {

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

    NodeT *aux_prev = pHead;                // Will point to the node before the position
    NodeT *aux = pHead->getNext();          // Will point to the node at the position
    int curr_pos = 1;

    while (curr_pos != pos) {               // Traverse the list until the position is reached
        aux_prev = aux;
        aux = aux->getNext();
        curr_pos++;
    }

    auto* new_node_at = new NodeT(data, aux);  // The node at the position becomes the next node of the new node
    aux_prev->setNext(new_node_at);         // The node before the position points to the new node

    nodeCount++;                            // Increase the node count
}

template <typename NodeT>
void List<NodeT>::popFront() {
    if (pHead == nullptr) {                 // If the list is empty
        cout << "Can't delete anything, the list is empty." << endl;
        return;
    }

    NodeT* old_head = pHead;

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

template <typename NodeT>
void List<NodeT>::popBack() {
    if (pTail == nullptr) {                 // If the list is empty
        cout << "Can't delete anything, the list is empty." << endl;
        return;
    }

    NodeT* old_tail = pTail;

    if (this->getNodeCount() == 1) {        // If there is only one node the list becomes empty
        pHead = nullptr;
        pTail = nullptr;
    }
    else {
        NodeT* aux = pHead;
        while (aux->getNext() != pTail) {
            aux = aux->getNext();
        }

        aux->setNext(nullptr);              // The node before the last one becomes the last one
        pTail = aux;                        // Also becomes the pTail
    }

    delete old_tail;                        // Delete the old pTail
    nodeCount--;                            // Decrease the node count
}

template <typename NodeT>
void List<NodeT>::popAt(int pos) {
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

    NodeT* aux_prev = pHead;                // Will point to the node before the position
    NodeT* aux = pHead->getNext();          // Will point to the node to delete
    int curr_pos = 1;

    while (curr_pos != pos) {               // Traverse the list until the position is reached
        aux_prev = aux;
        aux = aux->getNext();
        curr_pos++;
    }

    aux_prev->setNext(aux->getNext());      // The node before the position points to the node after the position
    delete aux;                             // Delete the node at the position
    nodeCount--;                            // Decrease the node count
}

template <typename NodeT>
void List<NodeT>::setDataAtNode(int pos, typename NodeT::valType* newData) {
    if (pHead == nullptr || pos < 0 || pos >= nodeCount)    // Return nullptr for invalid position or empty list
        return;

    if (pos == 0) {                         // If the position is 0, calls setData on the head
        pHead->setData(newData);
        return;
    }

    if (pos == nodeCount - 1) {             // If the position is the last one, calls setData on the tail
        pTail->setData(newData);
        return;
    }

    NodeT *aux = pHead->getNext();
    int curr_pos = 1;

    while (curr_pos != pos) {               // Traverse the list until the position is reached
        aux = aux->getNext();
        curr_pos++;
    }

    aux->setData(newData);                  // Sets the new data
}

template <typename NodeT>
void List<NodeT>::swapNodesAt(int m, int n) {
    if (m < 0 || n < 0 || m >= nodeCount || n >= nodeCount) {     //validate the positions
        cout << "Invalid value." << endl;
        return;
    }

    if (m == n) {                           // If the positions are the same, there is nothing to do
        return;
    }

    NodeT *node_m = pHead;
    NodeT *node_n = pHead;

    for (int i = 0; i <= max(m, n); ++i) {  // Traverse the list to find the nodes at M and N
        if (i < m) {
            node_m = node_m->getNext();
        }

        if (i < n) {
            node_n = node_n->getNext();
        }
    }

    typename NodeT::valType* aux = node_m->getData();   // Swap the data of the nodes
    node_m->setData(node_n->getData());
    node_n->setData(aux);
}

template <typename NodeT>
NodeT* List<NodeT>::getHead() const {
    return pHead;
}

template <typename NodeT>
NodeT* List<NodeT>::getTail() const {
    return pTail;
}

template <typename NodeT>
NodeT* List<NodeT>::getNode(int pos) const {
    if (pHead == nullptr || pos < 0 || pos >= nodeCount)    // Return nullptr for invalid position or empty list
        return nullptr;

    if (pos == 0)                           // If the position is 0, call getHeadData
        return this->getHead();

    if (pos == nodeCount - 1)               // If the position is the last one, call getTailData
        return this->getTail();

    NodeT *aux = pHead->getNext();
    int curr_pos = 1;

    while (curr_pos != pos) {               // Traverse the list until the position is reached
        aux = aux->getNext();
        curr_pos++;
    }

    return aux;
}

template <typename NodeT>
typename NodeT::valType* List<NodeT>::getHeadData() const {
    return pHead ? pHead->getData() : nullptr;
}

template <typename NodeT>
typename NodeT::valType* List<NodeT>::getTailData() const {
    return pHead ? pTail->getData() : nullptr;
}

template <typename NodeT>
typename NodeT::valType* List<NodeT>::getDataAtNode(int pos) const {
    return getNode(pos) ? getNode(pos)->getData() : nullptr;
}

template <typename NodeT>
int List<NodeT>::getPos(typename NodeT::valType* data) const {

    NodeT *current = pHead;
    int pos = 0;

    while (current) {                       // Traverse the list until the node with the specified data is found
        if (*current->getData() == *data)
            return pos;
        current = current->getNext();
        pos++;
    }

    return -1;                              // Return -1 if the data is not found
}

template <typename NodeT>
int List<NodeT>::getNodeCount() const {
    return nodeCount;
}

template <typename NodeT>
bool List<NodeT>::isEmpty() const {
    return (nodeCount == 0);
}

template <typename NodeT>
bool List<NodeT>::contains(typename NodeT::valType* data) const {
    return getPos(data) != -1;
}

template <typename NodeT>
void List<NodeT>::printList() const{
    cout << "Start of list" << endl;
    NodeT *aux = pHead;

    while (aux) {                           // Traverse the list and print the data of each node while the pointer is not null
        if (aux->getData() != nullptr) {
            cout << aux->getData()->toString() << endl; // Dereference the pointer to the data, needs to overload the << operator
        }
        aux = aux->getNext();
    }

    cout << "End of list" << endl;
}

template <typename NodeT>
string List<NodeT>::toString() const {
    return "holi, soy una lista";
    // TODO: implementar bien el toString y el printList, testearlos
}