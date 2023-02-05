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
