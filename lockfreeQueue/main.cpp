#include <iostream>
#include "LockFreeQueue.cpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    slist<int>* intList = new slist<int>();
    intList->push_front(1);
    std::cout << intList->find(1) << std::endl;
    delete intList;
    return 0;
}

/**
 * Code explanation.
 * The queue consists of many nodes. We make the Node std::atomic<Node*>, by doing this we ensure that all nodes
 * have this atomic nature (meaning multiple threads can operate on each node
 * without causing race conditions). Since queues are nodes, if all nodes are are thread safe, the queue is thread safe.
 *
 * std::atomic gives programmers the power/control to choose synchronization and ordering constraints.
 * Usually we do atomic<int> data = 0. When we want to store/update/change data's value, we do
 * data.store(1, memory_order_release). When we need to read the value we do data.load(memory_order_acquire).
 * Summary: for store/update/change we use release, for read we use acquire.
 *
 * So how does programmer specify the ordering constraints? Using the memory_order_...
 * For memory_order_release it is used for store/update/change. No stores can be reordered wrt. the atomic store.
 * I.e. if they are before the atomic store in the source code, they will happen before the atomic store too.
 *
 * For memory_order_acquire it is used for load/read. No loads can be reordered wrt. the atomic load.
 * I.e. if they are after the atomic load in the source code, they will happen after the atomic load too.
 *
 * Initially we set head to be nullptr. In C++ better to use nullptr than NULL  because nullptr is convertible to
 * any pointer type.
 *
 * head = nullptr; same as head{nullptr}.
 *
 * All of my functions are using (const T& t). There are three different ways (const T, T&, or const T&). First: pass
 * a copy of the object that cannot be modified. (not good because need copy, remember move
 * semantics). Second: Pass a reference that can be modified. Third: a const reference to object. Third better than First
 * because of move semantics. And Third is better than Second because we do not want to change the state of the passed
 * reference.
 *
 * const at the end of the function means that function will not modify any data. This const is only added at the end of
 * the find function because that function do not modify anything. If you add const into a function that modifies something,
 * for example push/pop front. There will be an error.
 *
 * compare_exchange_weak(expected, newVal) returns bool. Compare atomic object contained value.
 * If contained value == expected, replace with newVal. If false, expected is replaced with contained value.
 *
 * When we use *new* keyword to dynamically allocate memory it wont be automatically deleted so we need to keep
 * in mind to delete something that created by *new*.
 */
