#include <iostream>
#include "LockFreeStack.cpp"
#include <thread>
#include <vector>
#include <unistd.h>

int main() {
    std::cout << "Hello, World!" << std::endl;
    slist<int> *intList = new slist<int> ();

//    std::vector<std::thread> threads;
//    for(int i = 0; i < 10; i++) {
//        std::thread t1(&slist<int>::push_front, intList,i);
//        threads.push_back(std::move(t1));
//        usleep(5);
//    }
//
//    for (auto & thread : threads) {
//        thread.join();
//    }
//    intList->printList();

    slist<int> *intList2 = new slist<int> ();
    std::vector<std::thread> threads2;

    intList2->push_front(1);

    std::thread t2(&slist<int>::pop_front, intList2);

    std::thread t3(&slist<int>::push_front, intList2,2);

    t2.join();
    t3.join();

    intList2->printList();




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
 * Initially I create the thread t1, to create a thead is std::thread t1(&slist<int>::push_front, intList,i);.
 * Then threads.push_back(t1) does not work because we are copying the thread.
 * Passing by value means that the parameter is copied into the function. That calls the copy constructor.
 * We CANNOT copy threads.
 *
 * Without the sleep function the order printed will not be 9,8,7... because we have no control over when threads start to run. We create them
 * and the OS will start a thread whenever it wants. If we want it to be printed in 9,8,7... we force the main thread to go sleep.
 *
 * When push front, we create a node, and assign newNode->next = head. To ensure its done, we do
 * while(!head.compare_exchange_weak(p->next, p)). compare_exchange_weak is true when head == p->next which is what
 * we want, then it will assign head to be p in an atomic statement. Since its true ->  !true -> break out.
 *
 * If head != p->next, p->next is replaced with head. so head.compare_...(head, p). This will be true, then p is assigned
 * to be new head. (Try to draw out with 2 threads with thread2 coming in and completing after thread 1 does p->next = head.
 *
 * For pop_front, we load the head. while the head is not null !head.compare...(p, p->next). If CAS is true, is simple, we just
 * assign head to be next of p.
 *
 * If head != p, head has changed, so expected is replaced with head. head.CAS(head, p->next). is true so head == p->next.
 * So will delete the new head. (Will not delete a node that was created)
 *
 *
 * When we use *new* keyword to dynamically allocate memory it wont be automatically deleted so we need to keep
 * in mind to delete something that created by *new*.
 */
