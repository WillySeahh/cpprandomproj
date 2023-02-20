//
// Created by Willy Seah on 20/2/23.
//

#include "normalParentChild.h"
#include <iostream>

using namespace std;

void normalParentChild::parentFunction() {
    cout << "This is parent function" << endl;
}

void normalChild::childFunction() {
    cout << "This is child 1 function" << endl;
}

void normalChildTwo::childFunction() {
    cout << "This is child 2 function" << endl;
}
