#include <iostream>
using namespace std;

// We can write:
class Example {
public:
    int x = 5;
    const int y = 5;
};
/*
    This is completely valid since C++11.
    Whenever an Example object is created, 
    initialize its x member to 5 unless another initializer is provided.

    Example a;
    Example b;

    std::cout << a.x;  // 5
    std::cout << b.x;  // 5

    There is no problem with this because x belongs to each object.
*/

/*
    So why is static different?

    class Example {
    public:
        static int x;
    };

    Here x is not part of each object.
    Instead, there is one shared x for the entire class:

    Example object A ─┐
    Example object B ─┼──> one shared x
    Example object C ─┘

    That's why you can do:
    Example::x = 10;
*/

/*
    The old problem: static int x

    Before C++17, this:

    class Example {
    public:
        static int x;
    };
    was only a declaration.

    It told the compiler:   "There is a static variable called x somewhere."
    But it did not define/create the storage for it.
    So you had to define it separately: int Example::x = 5;

    Usually in a .cpp file.

    Why couldn't we simply write this before C++17?
    class Example {
    public:
        static int x = 5;  // ❌ before C++17
    };

    Because the compiler treated the in-class declaration as a declaration, 
    while the actual definition/storage needed to exist once somewhere.
    This was connected to the One Definition Rule (ODR).
*/

// Now the inline part
class Example_ {
    public:
        static inline int x = 5;
};
// This means: 
// This is the definition of x, and it is okay if this definition appears in multiple translation units.


/*
    What does inline solve?

    inline tells the linker:
    Yes, you may see this definition in multiple translation units. They all refer to the same variable.
*/
static inline int x = 5;
// can safely live in a header.

/*
    Cenceptually:

    Example.h
            ↓
    ┌───────────────┐
    │ static inline │
    │    x = 5      │
    └───────────────┘
              ↓
    ┌─────────┬─────────┐
    ↓         ↓
    main.cpp  test.cpp
    ↓              ↓
    same logical Example::x

    There is still one shared variable, not one x per .cpp file.
*/


/* Global variables have the same problem. */
// Without inline:
int global_value = 5;  // ❌ dangerous

/* 
    if:
    main.cpp
    #include "Example.h"

    and:
    test.cpp
    #include "Example.h"

    then both translation units contain:
    int global_value = 42;

    The linker sees:
    global_value
    global_value

    and says:   ❌ "You defined the same global variable twice."

    With C++17: 
    inline int global_value = 42;
    multiple translation units can contain that definition, and they all refer to the same variable.
*/

/*
    Why is static mentioned with inline?
*/
class Widget {
public:
    static inline int count = 0;
};
// static means: One variable shared by all Widget objects.
// inline means: Its definition can safely live in a header and appear in multiple translation units.

static inline int count = 0;
// means: allow this definition to be included from a header.

/*
    inline
        ↓
    allows the same definition to appear in multiple translation units
        ↓
    without violating the ODR
*/

// Final Example:
class Example__ {
public:
    int x = 5;          // one shared x per object;
    const int y = 5;    // one shared constsnt per object
    static int z;       // one shared z, old C++: define elsewhere
    static inline int w = 5; // one whared w, definition can be in header
};

int main() {


    return 0;
}