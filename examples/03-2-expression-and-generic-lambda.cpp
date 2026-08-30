#include <iostream>
#include <memory>
using namespace std;

/*  
    2. Generic Lambda  

    The `auto` keyword cannot be used in lambda parameters in C++11. 
    Starting with C++14, lambda parameters can use `auto`,
    allowing lambdas to accept different types, similar to templates.
*/

// Recall that in usual functions: 
// void print(auto x, auto y);  // ❌ 'auto' is not allowed here
void lambda_generic() {
    auto generic = [](auto x, auto y) {
        return x + y;
    };

    cout << "generic: " << generic(1, 2) << endl;
    cout << "generic: " << generic(1.1, 2.2) << endl;
}


int main() {

    /*  1. Expression capture  */

    // 1. Before C++14: capture existing variables:
    int a = 10;
    auto lambda1 = [a]() {
        cout << a << endl; 
    };
    // [a] means: "Create a copy of the existing variable a inside the lambda."


    // 2. C++14: create and initialize a new captured variable
    [v1 = 1]() {
        cout << "v1: " << v1 << endl;
    }();
    // Here, v1 didn't exist before.
    // Create a variable called v1 inside the lambda and initialize it with 1.
    // And the type is deduced like auto:

    // 3. Why std::move(important)?
    auto important = std::make_unique<int>(1);

    cout << important << endl;   // address
    cout << *important << endl;  // value

    // A unique_ptr cannot be copied:
    // But it can be moved:  auto v2 = std::move(important);  // ✅
    auto add = [v1 = 1, v2 = std::move(important)](int x, int y) {
        return x + y + v1 + (*v2);
    };

    cout << "add: " << add(3, 4) << endl;


    //  2. Generic Lambda  
    lambda_generic();
    

    return 0;
}