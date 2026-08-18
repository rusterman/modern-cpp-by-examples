#include <iostream>
using namespace std;

/*
    Modern C++ Recommendations:
     - Use constexpr when the value is known at compile time and you want the compiler to guarantee it.
     - Use const when the value should not change after initialization but may only be known at runtime.
     - Avoid #define for constants. It is still useful for preprocessor tasks such as conditional compilation

     Do I need text substitution before compilation?
            │
         Yes ─────────► #define
            │
            No
            │
         Is the value guaranteed to be known at compile time?
            │
         Yes ─────────► constexpr
            │
            No
            │
         Should the value stay unchanged after initialization?
            │
         Yes ─────────► const
            │
            No
            │
     Use a regular variable
*/

#define LEN 10

int len_foo() {
    int i = 2;
    return i;
}

constexpr int len_foo_constexpr() {
    return 5;
}

constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n - 1) + fibonacci (n - 2);
}

constexpr int fibonacci_(const int n) {
    if(n == 1) return 1;
    if(n == 2) return 1;
    return fibonacci_(n-1) + fibonacci_(n-2);
}


int main() {

    system("clear");
    
    char arr_1[10];     // legal
    char arr_2[LEN];    // legal

    int len = 10;
    char arr_3[len];    // illegal

    const int len_2 = len + 1;
    constexpr int len_2_conxtexpr = 1 + 2 + 3;

    char arr_4[len_2];  // illegal
    char arr_5[len_2_conxtexpr];    // legal

    char arr_6[len_foo() + 5];  // illegal
    char arr_7[len_foo_constexpr() + 1];    // legal

    cout << fibonacci(10) << endl;
    cout << fibonacci_(10) << endl;

    int t;
    cin >> t;

    const int T = t;
    // constexpr int T = t;   // illegal

    cout << T << endl;

    return 0;
}