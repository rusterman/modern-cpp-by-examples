#include <iostream>
using namespace std;

// math.h  - assume this lib
template<typename T>
T square(T x) {
    return x * x;
}

/*
    Now imagine three different files
    - main.cpp
    - utils.cpp
    - tests.cpp
*/

// all of them include
#include "math.h"

// and all of them use
int res = square<int>(5);

/*
    Graphically:

    main.cpp
    ------------
    square<int>()
        ↓
    Compiler creates
    int square(int)


    utils.cpp
    ------------
    square<int>()
        ↓
    Compiler creates
    int square(int)


    tests.cpp
    ------------
    square<int>()
        ↓
    Compiler creates
    int square(int)

    Then linker removes the duplicates!
    The compiler already spent time generating the same template code three times

    Now imagine heavy templates like:
    vector<int>
    vector<double>
    vectorstring>

    If 200 files include <vector>, every file may instantiate many of those templates.
    Compilation becomes slower.
*/

// C++11 solution: extern template
//extern template int square<int>(int);

/*
    main.cpp
    ------------
    uses square<int>()

    Compiler:
    "I know it exists.
    I won't generate it."

    utils.cpp
    ------------
    Compiler:
    "I won't generate it."

    tests.cpp
    ------------
    Compiler:
    "I won't generate it."

    math.cpp
    ------------
    Compiler:
    Generate square<int>()

    Only one file performs the expensive work.
*/

/*
    Difference

    template class MyClass<int>;
    means Instantiate here

    extern template class MyClass<int>;
    means Do not instantiate it here, someone else will.
*/

// Nested templates
vector<vector<int>> res1;
vector<vector<int> > res2;
vector<
    vector<int>
> res3;

// Weird example
template<bool T>
class MagicType {
    bool magic = T;
};

vector<MagicType<(1 > 2)>> magic;

int main() {

    return 0;
}