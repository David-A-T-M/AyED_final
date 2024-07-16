/*
 * Class queue, inherits from List and can be used with any type of Node
 */
#pragma once
#include "List.hpp"

using namespace std;

template <typename NodeT>
class Queue : public List<NodeT> {
private:

public:
    Queue();
    ~Queue();
    void enqueue(typename NodeT::valType*);
    void dequeue();
    void printList() const override;
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