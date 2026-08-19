#include <iostream>
using namespace std;

/*
    1. Delegate constructor

    C++11 delegating constructors let one constructor delegate its initialization 
    to another constructor of the same class removing duplication.
*/

class Base {
public:
    int value1;
    int value2;

    Base() {
        value1 = 1;
    }

    Base (int val) : Base() {   // deligate Base() constructor
        value2 = val;
    }
};


// 2. Inheritance constructor
class Subclass : public Base {
public:
    using Base::Base;  // using Base::Base; means: “make the constructors of Base available as constructors of Subclass.”
};
/*
    Conceptually, C++ allows this to behave as if Subclass had:
    Subclass(int val) : Base(val) {}

    using normally means bring this name into this scope
    In our case using Base:Base - means bring Base class Base constructor in current scope i.e. to Subclass public scope
    Bring Base's constructors into Subclass's constructor set
*/


/*
    3. Explicit virtual function overwrite

    - SubClass::foo may not be a programmer trying to overload a virtual function, just adding a function with the same name
    - Another possible scenario is that when the virtual function of the base class is deleted
        1. the subclass owns the old function and no longer overloads the virtual function
        2. turns it into a normal class method, which has catastrophic consequences
    - C++11 introduces the two keywords 'override' and 'final' to prevent this from happening
*/
struct Base_ {
    virtual void foo();
};

struct SubClass_: Base_ {
    void foo();
};

struct Base__ {
    virtual void foo(int);
};
struct SubClass__: Base__ {
    virtual void foo(int) override; // legal
    // virtual void foo(float) override; // illegal, no virtual function in super class
};


// 4. Final
struct Base___ {
    virtual void foo() final;
};

struct SubClass1___ final: Base___ {
}; // legal

// struct SubClass2___ : SubClass1___ {}; // illegal, SubClass1 has final
// struct SubClass3___: Base___ { void foo(); } // illegal, foo has final


/*
    5. Explicit delete default function
    
    In traditional C++, if the programmer does not provide it, the compiler will default to generating
        1. default constructors
        2. default copy constructs, 
        3. default assignment operators 
        4. default destructors for the object
        5. new
        6. delete

    Besides, C++ also defines operators such as new delete for all classes.
    This part of the function can be overridden when the programmer needs it.
*/

class Magic {
public:
    Magic() = default;  // Use the compiler-generated default constructor. So Magic m; is allowed.
    Magic& operator=(const Magic&) = delete;  // Disable copy assignment.
    /*
        So this is forbidden:
        Magic a;
        Magic b;
        b = a;  // ❌
    */
    Magic(int magic_number);
};


/*
    6. Strongly typed Enumerations

    - C++11 enum class makes enums safer and prevents name conflicts
*/
enum Color {
    RED,
    GREEN
};
enum TraffficLight {
    RED_LIGHT,
    YELLOW
};
/*
    Traditional enum values (RED, GREEN, etc.) are placed directly into the surrounding scope.
    So two different enums cannot have the same value name.
*/

// Also, traditional enums can behave like integers:
int x = RED;   // ✅ allowed

// Enum Class
enum class Color_ {
    RED,
    GREEN
};
enum class TrafficLight_ {
    RED,
    YELLOW
};
// Now this is perfectly fine because the names are inside their enum's scope.

// We access them with ::
Color_ c = Color_::RED;
TrafficLight_ t = TrafficLight_::RED;

/*  Strong type safety  */
// With traditional enums:
enum Scale { ZOOM, DISTANCE };
enum Size { SMALL, LARGE };

Scale z = ZOOM;
Size  l = LARGE;
// if (z == l) { }  // ⚠️ traditional enum can allow this

// With Enum Class
enum class Scale_ { ZOOM, DISTANCE };
enum class Size_ { SMALL, LARGE };

Scale_ z_ = Scale_::ZOOM;
Size_  l_ = Size_::LARGE;
// if (z_ == l_) {}  // ❌ compile error, Because Color_ and Siz_e are different types.

// What does : unsigned int mean?
// it specifies the underlying integer type used to store the enum: unsigned int
enum class MyEnum : unsigned int {
    VALUE1,
    VALUE2,
    VALUE3 = 100,
    VALUE4 = 100
};

// One more important difference
// With enum class, you cannot automatically treat the value as an integer:
enum class Color__ {
    RED,
    GREEN
};
// int num = Color__::GREEN; // ❌

// But if we want:
int num = static_cast<int>(Color__::RED);

// Old enum: These names are basically integers.
// enum class: These are distinct types with their own names and scope.
// For modern C++, prefer enum class in most cases!


int main() {
    if (z == l) {} // ⚠️ traditional enum can allow this
    
    Base b(2);
    cout << b.value1 << " " << b.value2 << endl;

    Subclass s(3);
    cout << s.value1 << " " << s.value2 << endl;
    /*
        Subclass s(3)
            ↓
        Base(int value)
            ↓
        Base() → value1 = 1
            ↓
        value2 = 3
    */

    if (z == l) { }  // ⚠️ traditional enum can allow this

    return 0;
}
