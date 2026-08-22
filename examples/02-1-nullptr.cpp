#include <iostream>
#include <type_traits>
using namespace std;

/*
    Historically, C++ allowed: 
    int* p = 0;

    But 0 itself is still an integer. That's the problem.

    NULL is not a C++ keyword.
    It is a macro provided by the implementation/library.
    Historically, it might be something like:   #define NULL 0
    or in C:    define NULL ((void*)0)

    C++11 introduced: nullptr is specifically designed to represent a null pointer.
    And unlike 0, it is not an integer.

    decltype(expression) asks: What is the type of this expression?
*/

void foo(int) {
    cout << "int" << endl;
}

void foo(char*) {
    cout << "pointer" << endl;
}
/*
    0
    │
    └── integer
        ├── foo(int)       ✅
        └── foo(char*)     conversion

    nullptr
    │
    └── nullptr_t
        └── foo(char*)     ✅ pointer conversion
*/


/*
    What does ((void*)0) actually mean?
    - There are two things happening.
    - Take the integer 0 and explicitly cast it to void*.
    - The resulting pointer is a null pointer value.
    - void* means: A pointer to an object of an unspecified type.
*/
double x = 3.4;
void* ptr = &x;

int main() {

    system("clear");

    char *ch1 = NULL;
    char *ch2 = nullptr;

    cout << NULL << " " << (size_t)(nullptr) << endl;

    cout << std::is_same<decltype(NULL), decltype(0)>::value << endl;
    cout << std::is_same<decltype(NULL), decltype(nullptr)>::value << endl;
    
    int a = 20;
    decltype(a) b = 22;
    /*
        Can we print decltype? Not directly.
        It's like asking: "cout << int" You can't print a type directly.
    */

    return 0;
}