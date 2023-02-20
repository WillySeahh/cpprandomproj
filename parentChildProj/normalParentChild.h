//
// Created by Willy Seah on 20/2/23.
//

#ifndef PARENTCHILDPROJ_NORMALPARENTCHILD_H
#define PARENTCHILDPROJ_NORMALPARENTCHILD_H

#include <iostream>
#include <string>

using namespace std;

class normalParentChild {
public:
    void parentFunction();
};

class normalChild : public normalParentChild {
public:
    void childFunction();
};

class normalChildTwo : public normalParentChild {
public:
    void childFunction();
};


#endif //PARENTCHILDPROJ_NORMALPARENTCHILD_H
