/**
 * @class Queue
 * @brief Composed of generic nodes that store a pointer to the data of the type that the node can store.
 * @tparam NodeT Type of the nodes to compose the queue.
 */
#pragma once
#include "List.hpp"

using namespace std;

template <typename NodeT>
class Queue : public List<NodeT> {
private:

public:
    /**
     * @brief Default constructor.
     */
    Queue();
    /**
     * @brief Default destructor.
     */
    ~Queue();
    /**
     * @brief Enqueues a new node with the specified data
     *        The data type must match the type that NodeT can store.
     * @param data Pointer to the data to be stored in the new node.
     */
    void enqueue(typename NodeT::valType *data);
    /**
     * @brief Dequeues the next element from the queue.
     *        If the queue is empty, it prints a message and does nothing.
     */
    void dequeue();
    /**
     * @brief Prints the contents of the queue from front to back.
     *        This method overrides the printList method from the List class.
     */
    void printList() const override;
    /**
     * @brief Returns a string representation of the queue.
     * @return A string representation of the queue.
     */
    string toString() const;
};

template <class NodeT>
Queue<NodeT>::Queue() = default;

template <class NodeT>
Queue<NodeT>::~Queue() = default;

template <class NodeT>
void Queue<NodeT>::enqueue(typename NodeT::valType *data) {
    this->pushBack(data);
}

template <class NodeT>
void Queue<NodeT>::dequeue() {
    if (this->getNodeCount() == 0){
        cout << "Can't dequeue, queue is empty" << endl;
        return;
    }
    this->popFront();
}

template <typename NodeT>
void Queue<NodeT>::printList() const {
    cout << "Inicio de cola" << endl;
    NodeT *aux = this->getHead();

    while (aux) {
        if (aux->getData() != nullptr) {
            cout << aux->getData()->toString() << endl;
        }
        aux = aux->getNext();
    }

    cout << "Fin de cola" << endl;
}

template<typename NodeT>
string Queue<NodeT>::toString() const {
    return "holi soy una cola";
    //TODO
}