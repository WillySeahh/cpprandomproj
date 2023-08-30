//
// Created by Willy Seah on 28/8/23.
//


#include <iostream>

using namespace std;

template<class T>
class SharedPtr {
private:
    T* ptr = nullptr;

    //for count must use a pointer because a static will be shared by ALL instance
    //pointer we can pass it on to the same object.
    int *refCount = nullptr;

    void __cleanup__()
    {
        (*refCount)--;
        if (*refCount == 0)
        {
            if (nullptr != ptr)
                delete ptr;
            delete refCount;
        }
    }

public:
    SharedPtr() : ptr(nullptr), refCount(new int (0)) {

    }

    SharedPtr(T* ptr) : ptr(ptr), refCount(new int (1)) { //normal constructor

    }

    SharedPtr(SharedPtr& other) : ptr(other.ptr), refCount(other.refCount) { //normal constructor
        (*refCount)++;
    }


    //Copy constructor
    SharedPtr(const SharedPtr &obj) {
        //copy constructor
        this->ptr = obj.ptr; //this pointer share the parameter ptr
        this->refCount = obj.refCount; //share refCount, this pointer will point to that obj's int pointer.
        //so will point to the same int variable.

        if (nullptr != obj.ptr) {
            *(this->refCount)++; //will increment the int, so all ptr pointing to this will see this new incremented value
        }
    }

    SharedPtr& operator=(const SharedPtr& obj) {
        //assignment operator must return address else got redundant copies
        /**
         * After assignment we need to reduce count because, this is pointing to new thing,
         */

        if (this != &obj){
            *(refCount) --;
            if (*(refCount) == 0) {
                delete ptr;
                delete refCount;
            }
            ptr = obj.ptr;
            refCount = obj.refCount;
            *(refCount)++;
        }
        return *this;
    }

    SharedPtr(SharedPtr&& dyingObject) {
        this->refCount = dyingObject.refCount;
        this->ptr = dyingObject.ptr;

        dyingObject.ptr = nullptr;
        dyingObject.refCount = nullptr;
        //no need to increment because this is just moving it
    }

    SharedPtr& operator=(SharedPtr&& dyingObject) {

        if (this != &dyingObject) {
            *(refCount) --;
            if (*(refCount) == 0) {
                delete ptr;
                delete refCount;
            }
            ptr = dyingObject.ptr;
            refCount = dyingObject.refCount;
            dyingObject.refCount = nullptr;
            dyingObject.ptr = nullptr;
        }
        return *this;
    }

    T* operator->() const
    {
        return this->ptr;
    }
    T& operator*() const
    {
        return *(this->ptr);
    }

    int get_count() const
    {
        return *refCount; // *this->refCount
    }

    T* get() const
    {
        return this->ptr;
    }

    ~SharedPtr() // destructor
    {
        __cleanup__();
    }

};


class Box
{
public:
    int length, width, height;
    Box() : length(0), width(0), height(0)
    {
    }
};
int main()
{
    SharedPtr<Box> obj;
    cout << obj.get_count() << endl; // prints 0
    SharedPtr<Box> box1(new Box());
    cout << box1.get_count() << endl; // prints 1
    SharedPtr<Box> box2(box1); // calls copy constructor
    cout << box1.get_count() << endl; // prints 2
    cout << box2.get_count() << endl; // also prints 2

    obj = std::move(box2);

    cout << obj.get_count() << endl; // also prints 2





    return 0;
}
