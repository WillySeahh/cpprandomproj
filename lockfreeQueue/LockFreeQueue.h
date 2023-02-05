//
// Created by Willy Seah on 5/2/23.
//
#include <atomic>

#ifndef LOCKFREEQUEUE_LOCKFREEQUEUE_H
#define LOCKFREEQUEUE_LOCKFREEQUEUE_H

#endif //LOCKFREEQUEUE_LOCKFREEQUEUE_H

template<typename T>
class slist{
public:
    slist();
    ~slist();
    T* find(const T& t) const;
    void push_front(const T& t);
    void pop_front(const T& t);
private:
    struct Node{
        T t;
        Node* next;
    };

    std::atomic<Node*> head{nullptr};
};
