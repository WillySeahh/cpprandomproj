//
// Created by Willy Seah on 5/2/23.
//
#include "LockFreeQueue.h"
#include <iostream>

template<typename T>
slist<T>::slist() {
    //empty constructor
    std::cout << "Created a SList" << std::endl;
}

template<typename T>
slist<T>::~slist() {
    std::cout << "Destroying SList" << std::endl;
    Node* first = head.load();
    while (first != NULL) {
        auto unlinked = first;
        first = first->next;
        delete unlinked;
    }
}

template<typename T>
T* slist<T>::find(const T &t) const {
    Node* p = head.load();
    while (p != NULL && p->t != t) {
        p = p->next;
    }
    return p? &p->t : nullptr;
}

template<typename T>
void slist<T>::push_front(const T &t) {
    Node* p = new Node();
    p->t = t;
    p->next = head;
    while (!head.compare_exchange_weak(p->next, p)) {
        /**
         * If head == p->next means is correct, then update head as p.
         * Checks until it is correct.
         * If false it means change p->next in parameter to p. So it check if head == p. which is our eventual goal.
         */
    }
}

template<typename T>
void slist<T>::pop_front(const T &t) {
    Node* p = head.load();
    while (p && !head.compare_exchange_weak(p, p->next)) {

    }
    delete p;
}

