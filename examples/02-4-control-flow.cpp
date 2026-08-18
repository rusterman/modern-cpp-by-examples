#include <iostream>
#include <type_traits>  // the library that lets the compiler to ask questions about types
#include <vector>
#include <algorithm>
using namespace std;

/*
    Your Code -> 
    Compiler -> 
    Machine Code -> 
    Program Runs
*/

// The compiler already knows that the x is 5 before program starts
constexpr int x = 5; 
constexpr int y = x + 3;  // the compiler computes at compile time


// The function is executed before program starts
constexpr int square(int x) {
    return x * x;
}
/*
    During compilation: square(4) -> 16 -> store 16
*/


// Use case for "if constexpr"
template<typename T>
auto print_type_info(const T& t) {
    if constexpr (is_integral<T>::value) {
        return t + 5;
    } else {
        return t + 0.0001;
    }
}
/*
    print_type_info(5):
        -> so type deduced is T = int
        -> compiler removes else statment completely
        -> and it becomes:
        int print_type_info(const int& t) 
        {
            return t + 1;
        }
    
    print_type_info(3.14):
        -> type deduced is T = double
        -> comipler removes if statement completely
        -> and it becomes:
        double print_type_info(const double& t)
        {
            return t + 0.0001;
        }
*/


// Why "if constexpr" is important!
//Without "if constexpr" the compiler will compile both brnaches and if T=int the x will not have "someFunction()" property
template<typename T>
auto foo(T x) {
    // if constexpr (is_integral<T>::value) {  -> condition -> true -> delete else branch
    if (is_integral<T>::value) {
        return x + 5;
    } else {
        return x.someFunction();   
    }
}

/*
    Visualization:
        1. Template -> Compile both branches -> Program runs -> Choose branch
        2. Template -> Evaluate condition -> Choose branch -> delete unused branch -> compile remaining branch
*/


// Use Case - 2:
template<typename T>
void print(T value) 
{
    if constexpr (is_integral<T>::value) {
        cout << "Integer: " << value << endl;
    }
    else {
        cout << "No integer: " << value << endl;
    }
}


int main() {

    cout << square(4) << endl;

    // What is "if constexpr" ???
    int z = 5;

    if (z > 10) {   // the compiler does not know whether the condition is true, only when program is running
        
    }

    if constexpr (y > 10) { // the compiler already knows whether the condition is true
        /*
            Compiler -> condition? -> True -> Delete the else branch! -> Generate executable 
        */
    }

    // is_integral gives us true for integral types like int, char, bool
    cout << is_integral<int>::value << endl;
    cout << is_integral<bool>::value << endl;
    cout << is_integral<char>::value << endl;
    cout << is_integral<float>::value << endl;
    cout << is_integral<double>::value << endl;

    cout << print_type_info(5) << endl;
    cout << print_type_info(3.14) << endl;

    print(10);
    print(3.14);

    // Range based for loop
    vector<int> vec = {1, 2, 3, 4};

    if (auto itr = find(vec.begin(), vec.end(), 3); itr != vec.end()) {
        *itr = 4;
    }

    for (const auto& elemet : vec) {
        cout << elemet << " ";  // read-only
    } cout << endl;

    for (auto& element : vec) {
        element++;  // writable
    }

    for (const auto& e : vec) {
        cout << e << " ";
    }


    return 0;
}