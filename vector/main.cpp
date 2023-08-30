//
// Created by Willy Seah on 28/8/23.
//
#include <iostream>

using namespace std;

template <typename T>
class MyVector {
private:
    T* arr;
    int size; //tells us how many element in vector, and where is the next free index
    int capacity;

public:
    MyVector() {
        arr = new T[1];
        capacity = 1;
        size = 0;
    }

    ~MyVector() {
        delete[] arr; //delete for arrays
    }

    void push_back(T element) {
        if (size == capacity) {
            T* temp = new T[2 * capacity];

            for(int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }

            delete[] arr;
            arr = temp;
            capacity *= 2;
        }

        arr[size] = element;
        size++;
    }

    void push(T data, int index) {
        if (index == capacity) {
            push_back(data);
        } else {
            arr[index] = data;
        }
    }

    T get(int index) {
        if (index < size) {
            return arr[index];
        }
    }

    void pop() {
        size--;
    }

    int getSize() {
        return size;
    }

    int getCapacity() {
        return capacity;
    }

    void print()
    {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }




};


int main() {

    MyVector<int> v;
    MyVector<char> v1;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);
    v1.push_back(71);
    v1.push_back(72);
    v1.push_back(73);
    v1.push_back(74);

    cout << "Vector size : " << v.getSize() << endl;
    cout << "Vector capacity : " << v.getCapacity() << endl;

    cout << "Vector elements : ";
    v.print();

    v.push(100, 1);

    cout << "\nAfter updating 1st index" << endl;

    cout << "Vector elements of type int : " << endl;
    v.print();
    // This was possible because we used templates
    cout << "Vector elements of type char : " << endl;
    v1.print();
    cout << "Element at 1st index of type int: " << v.get(1)
         << endl;
    cout << "Element at 1st index of type char: "
         << v1.get(1) << endl;

    v.pop();
    v1.pop();

    cout << "\nAfter deleting last element" << endl;

    cout << "Vector size of type int: " << v.getSize() << endl;
    cout << "Vector size of type char: " << v1.getSize()
         << endl;
    cout << "Vector capacity of type int : "
         << v.getCapacity() << endl;
    cout << "Vector capacity of type char : "
         << v1.getCapacity() << endl;

    cout << "Vector elements of type int: ";
    v.print();
    cout << "Vector elements of type char: ";
    v1.print();

    return 0;
}
