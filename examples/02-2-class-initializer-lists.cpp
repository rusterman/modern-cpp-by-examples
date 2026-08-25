#include <iostream>
using namespace std;

/*
    1. Initializer lists are one of the most important C++ constructor concepts, 
    especially once you understand const, references, inheritance, and member objects.

    An initializer list is the part after a constructor's :
*/
class Person {
private:
    std::string name;
    int age;

public:
    Person(std::string n, int a) : name(n), age(a) {}
};
// : name(n), age(a) is the constructor initializer list.


/*
    2. Why do we need it?
    The most important thing to understand is: C++ objects have two different stages

    C++ must first construct/initialize the members:
    Person object
        │
        ├── name  → constructed
        └── age   → initialized

    Only after all members have been initialized does the constructor body execute!
        1. Construct name
        2. Initialize age
        3. Enter constructor body
*/


/*
    3. Initializer list vs assignment

    Consider:
*/
class Person_ {
    string name;
    int age;

public:
    Person_(string n, int a) {
        name = n;
        age = a;
    }
};
/*
    You might think this means:
    create name
    create age

    then:
    name = n
    age = a

    So we're doing:
    construct name
        ↓
    assign n to name

    Instead, with:
    Person(std::string n, int a): name(n), age(a)
    {
    }

    we do:
    construct name directly with n
    construct age with a
*/


/***  Mandatory Use Cases  ***/

// Case-1: const members
class Person1 {
public:
    const int age;
    Person1(int a) : age(a) {}
};
/*
    Person(int a)
    {
        age = a; // ❌
    }
    
    must be initialized when the object is created.
*/


// Case-2: References also require initializer lists
class Person2 {
    int& age;
public:
    Person2(int& a) : age(a) {}
};


// Case-3: Object that do not have default constructors
class Engine {
public:
    Engine(int horsepower) {

    }
};

class Car {
    Engine engine;
public:
    Car(int hp) : engine(hp) {}
    // Car(int hp) { // too late }
};


// Case-4: Memeber Objects are constructed before the constructor body
class Engine_ {
public:
    Engine_(int hp) {
        cout << "Engine constructed\n";
    }
};

class Car_ {
    Engine_ engine;

public:
    Car_() : engine(200)
    {
        cout << "Car constructed\n";
    }
};
/*
    Engine constructed
        ↓
    Car constructor body
            ↓
    Car constructed

    The constructor body does NOT construct members.
    The members have already been constructed by the time the body starts.
*/


// UseCase-1: Initializer lists are also used to initialize the base class.
class Animal {
public:
    Animal(string name) {
    }
};

class Dog : public Animal {
public:
    Dog(string name) : Animal(name)
    {
    }
};


// UseCase-2: Initializer list can call different constructors
class Database {
public:
    Database (string host, int port) {
    }
};

class Application {
    Database db;
public:
    Application() : db("localhost", 5432) {

    }
};


// UseCase-3: Performance!!!
// Compare:
class Person__ {
    string name;

public:
    Person__(const string& n) {
        name = n;
    }
};
/*
    construct empty string
        ↓
    assign n
*/

// With: 
class Person___ {
    string name;

public:
    Person___(const string& n) : name(n) {  // construct string directly from n
    }
};


// Note-1: Initialization order — VERY important!
class Test {
    int a;
    int b;

public:
    Test() : b(20), a(10)
    {
    }
};
/*
    You might think:
    b → 20
    a → 10

    Wrong.
    C++ initializes members according to their declaration order:
    int a; // first
    int b; // second

    Therefore:
    a → 10
    b → 20
*/


// Note-2: The initializer list is not actually "inside" the constructor body
class Student {
    int age;
    string name;
public:
    Student(int a) : age(a) {  // initialization phase
        cout << "age is " << a << endl; // constructor body
    }
};
/*
    Object creation
        │
        ▼
    Initialize base classes
        │
        ▼
    Initialize members
        │
        ▼
    Execute constructor body
*/

int main() {


    return 0;
}