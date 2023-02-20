//
// Created by Willy Seah on 20/2/23.
//
#include <iostream>

using namespace std;
class Parent {
public:
    virtual void say() {
        cout << "1" << endl;
    }
};

class Child : public Parent {
public:
    void say()
    {
        std::cout << "2" << endl;
    }
};
