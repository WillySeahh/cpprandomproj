//
// Created by Willy Seah on 5/2/23.
//
#include "LockFreeStack.h"
#include <iostream>
#include <unistd.h>


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

    }
}

template<typename T>
void slist<T>::pop_front() {
    Node* p = head.load();
//    usleep(500);
    while (p && !head.compare_exchange_weak(p, p->next)) {

    }
    std::cout << "deleted " << std::endl;
    delete p;
}

template<typename T>
void slist<T>::printList() {
    Node* p = head.load();
    while (p != NULL) {
        std::cout << p->t << std::endl;
        p = p->next;
    }
}

