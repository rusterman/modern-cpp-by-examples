#include <iostream>
#include <functional>
using namespace std;

/*     
    Function Object Wrapper
    In C++, “things that can be called” come in many shapes — ordinary functions, function pointers,
    lambda expressions, and any object that overloads operator() — and they all have different types,
    which makes them hard to store and pass around uniformly. std::function exists precisely to solve
    this: it is a type-safe “container for callables” that can uniformly store, copy, and invoke any callable
    target, letting us handle “functions” as ordinary objects
*/

// 1. Pointer To a Function.
void print(int x = 0) {
    cout << x << endl;
}

void (*ptr)(int) = print;   // ptr points to foo.
/*
    void    → function returns void
    (*ptr)  → ptr is a pointer
    (int)   → function takes an int
*/


// 2. What does `using` do?
using Integer = int;    // using can create aliases for types.
Integer x = 5;

// It is especially useful for complicated types:
using Callback = void(int);

void execute(Callback callback) {
    callback(15);
}

// Ex-1:
using foo = void(int);  // This creates a type alias named foo.

void functional(foo f) {
    f(12);
}

auto f = [](int value) {
    cout << value << endl;
};


/*
    3. Why do we need std::function?
    C++ has many different things that can be called:
        - void foo_(int);
        - void (*ptr)(int);
        - [](int x) { ... }       // lambda
        - struct A {
            void operator()(int x) { ... }
          };

    All can be called like:
    - something(10);

    But their types are different.
    std::function gives them a common wrapper type:
    - std::function<void(int)>
    Meaning: "It can store anything that can be called with an int and returns void."
*/

// Ex-2:
void show(int x) {
    cout << x << endl;
}
std::function<void(int)> f1 = show;

std::function<int(int)> f2 = [](int x) {
    return x + x;
};

struct Printer {
    void operator()(int x) {
        cout << x << endl;
    }
};

std::function<void(int)> f3 = Printer{};

// Think of:
std::function<int(int)>;
/*
    as a box for callable objects with this interface:
    input:  int
    output: int
*/

// Ex-3:
int param(int para) {
    return para;
}


/*    
    Bind and Placeholder:   std::bind and std::placeholder

    - std::bind is basically a way to create a new callable by partially filling in the arguments of an existing function.
*/

// Example:
void add(int a, int b) {
    cout << a + b << endl;
}

auto a = std::bind(add, 10, 15);


// What are placeholders?
// Placeholders mean: "Don't give this argument now. Give it when the new callable is called."
auto l = std::bind(add, 10, std::placeholders::_1);  // _1 means the first argument given to l.

// Multiple placeholders
auto m = std::bind(
    add,
    std::placeholders::_1,  // _1 → first argument to m
    std::placeholders::_2   // _2 → second argument to m
);

// You can even reorder arguments:
auto n = std::bind(
    add,
    std::placeholders::_2,
    std::placeholders::_1
);


// The real problem std::bind solves and Why is bind useful?
// Imagine we have this function:
void sendEmail(int userId, string message) {
    cout << "Sending to user " << userId << ": " << message << endl;
}

// But some API expects a callback that takes only one argument:
void execute(function<void(string)> callback) {
    callback("Hello!");
}

// You want execute() to call: sendEmail(42, "Hello!");
// but execute() only gives your callback the message: callback("Hello!")
// So how do we connect them? bind solves exactly this
auto notification_callback = std::bind(
    sendEmail,
    42,
    std::placeholders::_1
);


int main() {

    // 1. Pointer To a Function.
    cout << ptr << endl;    // 1 - it is converted to bool
    cout << *ptr << endl;   // 1 - it is converted to bool
    cout << reinterpret_cast<void*>(ptr) << endl;   // 0x102edc530
    cout << reinterpret_cast<void*>(*ptr) << endl;  // 0x102edc530
    ptr(10);    // 10


    // Ex-1:
    f(13);  // call by lambda expression
    functional(f);  // call by function pointer


    // Ex-3
    std:function<int(int)> func = param;

    int important = 10;
    std::function<int(int)> func2 = [&](int value) -> int {
        return 1 + value + important;
    };

    cout << func(20) << endl;
    cout << func2(20) << endl;

    // bind exaple
    // bind creates a new callable f where 10 and 20 are already attached to add.
    a();  // 25

    // placeholder
    l(20);   // add 10 + 20
    l(50);   // add 10 + 50
    // add(10, _1) <- give later

    // Multiple placeholders
    m(10, 20);  // add(10, 20)
    n(20, 10);  // add(10, 20)

    // bind use case ex
    notification_callback("Hello!");

    return 0;
}