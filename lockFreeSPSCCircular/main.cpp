#include <iostream>
#include "CircularFifo.cpp"

int main() {

    // Obtained from https://www.codeproject.com/Articles/43510/Lock-Free-Single-Producer-Single-Consumer-Circular
    std::cout << "Hello, World!" << std::endl;

    CircularFifo<std::string , 2> queue;
    std::string s = "message1";
    queue.push(s);
    if (queue.push(s) == false) {
        std::cout << "full queue" << std::endl;
    }

    return 0;
}
