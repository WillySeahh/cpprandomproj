//
// Created by Willy Seah on 28/8/23.
//

#include <iostream>




template <class T>
class UniquePtr {

private:
    T* ptr = nullptr;

public:
    UniquePtr() : ptr(nullptr) {
        //initialize ptr as nullptr in the beginning
    }

    explicit UniquePtr(T* ptr = nullptr) : ptr(ptr) {
        //default is nullptr
    }

    UniquePtr(const UniquePtr& other) = delete; //cannot have copy constructor

    UniquePtr& operator = (const UniquePtr& other) = delete; //no copy assignment operator

    //this is to handle base pointing to derived class,because normal pointers can do that
    //T is base clas, U is derived class.
    template<class U>
    UniquePtr(UniquePtr<U> && right) :ptr(right.release()) {
        //implement move constructor
        //when i call UniquePtr with another Unique ptr, it will release the old one, and set whatever the old one
        //is pointing to, to the new one
    }

    //this is to handle base pointing to derived class, because normal pointers can do that
    //T is base clas, U is derived class.
    template<class U>
    UniquePtr& operator=(UniquePtr<U> && right) {
        //implement move constructor for assignment
        //when i call UniquePtr = old ptr, it will delete the right one and set this pointer to be pointing to the old one, and return this pointer
        reset(right.release());
        return *this;
    }


    //pointers when we call get, will return to that object.
    T* get() {
        return ptr;
    }

    T* operator-> () {
        return get();
    }

    T& operator* () {
        return *get();
    }

    ~UniquePtr() {
        reset(); //destroy uniquePtr, will destroy whatever it is pointing to
    }

    T* release() {
        //set ptr to nullptr, and return what it was pointing to
        auto oldPtr = ptr;
        ptr = nullptr;
        return oldPtr;
    }

    void reset(T* newPtr = nullptr) {
        auto oldPtr = release(); //what was it pointing to previously
        ptr = newPtr; //point to new things
        if (oldPtr != nullptr) {
            delete oldPtr;
        }
    }

};

class A {
    inline static int numberOfTimesACreated = 0; //need inline for static, either const static or inline static
    int myNum;

public:
    A() {
        myNum = ++numberOfTimesACreated;
        std::cout << "create object number :" << myNum << std::endl;
    }

    ~A() {
        std::cout << "destroy object number: " << myNum << std::endl;
    }
};

int main() {

    //should use make_unique
    auto a1 = new A;
    UniquePtr<A> uniquePtrToA(a1);

    auto a2 = new A;
    uniquePtrToA.reset(a2);

    std::unique_ptr<A> uPtrToADefaultLibrary = std::make_unique<A>();
    uPtrToADefaultLibrary.reset(); //reset is to delete, release is to release ownership. we want to use reset to delete


    std::cout<<"exiting main" << std::endl;

}