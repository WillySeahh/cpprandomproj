//
// Created by Willy Seah on 20/2/23.
//
#include <iostream>
#include <string>
using namespace std;

class Shape {
public:
    string name;
    int angles;

    string getName() {
        return name;
    }

    int getAngles() {
        return angles;
    }

    virtual float getArea() = 0; //pure virtual function
};

class Square: public Shape {
public:
    int length, width;

    float getArea() {
        return length * width;
    }
};


class Circle: public Shape {
public:
    int radius;

    float getArea() {
        return 3.14 * radius * radius;
    }

};


