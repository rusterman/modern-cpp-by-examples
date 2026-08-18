#include <iostream>

class Student1 {
public:
    std::string name;

    Student1(std::string n) {
        name = n;
    }
};  // allocate memory -> create default stirng -> destroy empty string -> copy new string

class Student2 {
public:
    std::string name;

    Student2 (std::string n) : name(n) {}
};  // allocate memory -> copy new string


class Image {
public:
    std::vector<int> pixels;

    Image(std::vector<int> p) { pixels = p; }
    Image(std::vector<int> p) : pixels(p) {}
};


// Sometime initializer list is necessary
class Student {
public:
    const int id;
    // Student(int x) { id = x; }  // error
    Student(int x) : id(x) {}
};

// Reference member
class Teacher {
public:
    int& ref;
    Teacher(int& r) : ref(r) {}
};


// Base Classes
class Animal {
public:
    Animal(int age) {}
};

class Dog : public Animal {
public:
    Dog(int age) : Animal(age) {}
    Dog(int age) { Animal(age); }   // error: Tries to create Dog before Animal
};


// Multiple memebers and initialization order does not matter!
class Student3 {
public:
    std::string name;
    int age;
    double gpa;
    // initialization does not matter
    Student3(std::string n, int a, double g) : age(a), name(n), gpa(g) {}
};


// In Modern C++ always use initialization list
class Person {
public:
    std::string name;
    int age;

    Person(std::string n, int a)
    : name(std::move(n)), age(a) {}
};


int main() {

    return 0;
}