#include <iostream>
#include <map>

using namespace std;

// typedef gives an alias name to an existing type
typedef int Integer;
Integer x = 5;

// Example
typedef vector<int> IntVector;
IntVector numbers;

// Usecase: Readibility
typedef map<string, vector<int>> MyMap;
MyMap data;

/*
    What is void* ?

    void - means an empty type, no type
    void print() - means no function return type
    void* - means pointer to unkown type
*/

int y = 5;
void *p = &x;  // we can not dereferense it

// later we can cast
int* real = (int*)p;

/*
    Why void* is useful?
    because it can point to:
    int
    double
    Person
    vector<int>
*/


// What is this?
int (*process)(void *);

/*
    process - is a variable name
    *process - process is a pointer
    (*process)(...) - means is a pointer to a function

    Finally:
    int (*process)(void *) - means 
    process -> pointer to a function -> take one void* -> return int 
*/

// Example function
int foo(void* data) {
    return 1;
}

int (*func)(void*) = foo;


// typdef simplifies it ex:
typedef int (*funcc)(void*);
funcc f;  // means int (*f)(void*);


// What is using? using is modern version of typdef but much more english like, examples:
using Integer = int;
using InVector = std::vector<int>;
using Process = int (*)(void*);

Process pro = foo;


// Alias Templates
template<typename T, typename U>
class MagicType {};

// Suppose
MagicType<int, string> obj1;
MagicType<double, string> obj2;
MagicType<bool, string> obj3;

/*
    What if we want just type by default like:
    MagicType<bool> obj
    Unfortunally MagicType<bool>, MagicType<int> or MagicType<double is illegal>
    typedef only aliases types, it can not alias templates:

    Template

    MagicType<T,U>
            ↓
    MagicType<int,string>
            ↓
    Actual type

    typedef works only after the type already exists.
*/


/*
    C++11 Solution 'using'
*/
template<typename T> 
using TrueDarkMagic = MagicType<vector<T>, string>;

TrueDarkMagic<int> tdm; 
// where compiler replaces it with: MagicType<vector<int>, string>

/*
    TrueDarkMagic<T>
        │
        ▼
    MagicType<
        std::vector<T>,
        std::string
    >
*/

// Summary
typedef double RationalNumber;   // alias of a type
using Ratinal = float;   // modern clearer type alias
void* ptr = nullptr;     // pointer to the unkown type
int (*function)(void*);  // a function pointer type taking void pointer as an argument returning integer type
using Function = int (*)(void*);   // 
template<typename T> using Alias = ClassName<int>;

int main() {

    cout << x << endl;
    cout << func(nullptr) << " is same as " << foo(nullptr) << endl;
    cout << pro(nullptr) << endl;

    return 0;
}