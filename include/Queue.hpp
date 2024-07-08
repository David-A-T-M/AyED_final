#pragma once
#include "List.hpp"

using namespace std;

template <typename T>
class Queue : public List<T> {
private:

public:
    Queue();
    ~Queue();
    void enqueue(T&);
    void dequeue();
};

template <class T>
Queue<T>::Queue() = default;

template <class T>
Queue<T>::~Queue() = default;

template <class T>
void Queue<T>::enqueue(T& data) {
    this->pushBack(data);
}

template <class T>
void Queue<T>::dequeue() {
    if (this->getNodeCount() == 0){
        cout << "Can't dequeue, queue is empty" << endl;
        return;
    }
    this->popFront();
}
