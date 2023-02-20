#include <iostream>

//#include "normalParentChild.h"
#include "normalParentChild.cpp"
#include "abstractClass.cpp"
#include "overRidingOrVirtual.cpp"


int main() {
    std::cout << "Hello, World!" << std::endl;

    normalParentChild nPC;
    nPC.parentFunction();

    normalChild nC;
    nC.childFunction();
    nC.parentFunction();

    normalChildTwo nCT;
    nCT.childFunction();
    nCT.parentFunction();

    /**
     * Some notes until here. child class can call parents method but when you extend from parents class
     * it is: public child: public parent, if there is no public before parent then it is implied to be private
     * and hence you cannot call the parent's function.
     *
     * For classes we usually put declaration in header file, eg just the function. name, and return type
     * not the implementation. The actual implementation is in the source (c++) file.
     *
     * Upon further research, header is commonly used for declaration and cpp source file is used for implementation.
     * But that is not a MUST. Some explanation: when #include statement is there, it replaces the include
     * with the contents of the file. So replacing header file include statement
     * with the actual content of header file.
     *
     * By doing a implementation in the header, it is implicitly declared as inlined. Meaning the compiler
     * should (but does not guarantee it will be inlined) inline that function. But if it does get inlined,
     * the contents of the function is directly used instead of jumping to that function and jumping back.
     * (reduce the call stack)
     * Hence making it faster. Therefore it allows the compiler to produce faster/more optimized machine code.
     *
     * Dont have to include the header file just need the source file
     *
     */

    cout << "end of first example" << endl << endl;

    Square square;
    Circle circle;

    //Shape shape; cannot create abstract class

    square.name = "square";
    square.length = 4;
    square.width = 6;
    square.angles = 4;

    circle.name = "Circle";
    circle.angles = 0; //if do not define this it will be a random number.
    circle.radius = 3;

    cout << "square angles " << square.getAngles() << endl;
    cout << "circle angles " << circle.getAngles() << endl;


    /**
     * Like java, we can force children to implement their function. in c++ we call it pure
     * virtual function. if a parent has pure virtual function (indicated by assigning 0), any
     * child class MUST override this function. abstract classes cannot be instantiated.
     * every abstract class must contain at least one pure virtual function.
     * So abstract classes are for pure virtual function.
     *
     * Normal virtual function is meant to be override and class can be instantiated.
     * But there is already the normal function over riding. So whats the difference between
     * virtual and function over riding?  Look below
     *
     */

    cout << "end of second example" << endl << endl;


    Child* a = new Child(); //should be 2
    a->say();
    Parent* p = new Parent(); //should be 1
    p->say();
    Parent* newP = new Child();
    newP->say(); //this IS 1 if there is NO VIRTUAL, if there is virtual then is 2.

    /**
     * when using new keyword it is dynamic allocation. That gives you a pointer.
     * Remember when you use new you have to delete it.
     *
     * But the main point of Virtual function is it uses the actual type (which is Child).
     * If no virtual function, just normal over riding, it will use the declare type which is
     * Parent.
     */

    cout << "end of third example" << endl << endl;




    return 0;
}
