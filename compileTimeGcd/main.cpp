
#include <iostream>

using namespace std;

template <int a, int b>
struct gcd {
    inline static constexpr int value = gcd < b, a % b >::value;
};

template < int a>
struct gcd <a, 0 > {
    inline static constexpr int value = a;
};

template<int a>
struct funStruct {
     static constexpr int value2 = 2*funStruct<a-1>::value2;
};

template<>
struct funStruct<0> {
    static constexpr int value2 = 1;
};

int main () {
    static_assert(gcd<5,15>::value == 5);
    static_assert(funStruct<8>::value2 == 256);
}