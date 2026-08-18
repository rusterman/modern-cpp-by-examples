#include <iostream>
#include <algorithm>
#include <memory>

using namespace std;

/*
    Templates allow you to write code once and use it with many different data types.
    Before templates existed, programmers had to duplicate the same code for every type.

    Templates are compile time code generation

    Advantages:
    - Code reuse
    - Type safety becuase errors are caught at compile time
    - Performance: no runtime dispatch is required for ordinary templates
    - Maintainability
    - Flexibility

    Limitations:
    - Error messages can be long and hard to interpret
    - Compilation can take longer
    - Using many tempaltes can  increase final binary size
*/

template<typename T>
T max_(T a, T b) {
    return a > b ? a : b;
}

template<typename T>
void swap_(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}


// Templates with Clasess
template<typename T>
class Box {
public:
    T value;
};


// Template With Multiple Paramaters
template<typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;
};


// Templates in the Standart Library
template<typename T>
class vector {
    // ...
};
/*
    vector<int>
    vector<double>
    vector<bool>
    vector<char>
    vector<string>
    vector<size_t>
*/

/*
    Containers:

    vector<int>
    map<string, int>
    set<double>
    list<Preson>
*/

/*
    Algorithms:
    sort(v.begin(), v.end()), find(), count() -> these algorithms can sort find count integers, floats, doubles, strings
*/


/*
    Smart Pointers
*/
shared_ptr<Pair<int, int>> pair;
unique_ptr<Box<string>> box;


int main() {

    // Template Type Deduction!
    cout << max_("abc", "bdc") << endl;
    cout << max_(3.12, 3.0) << endl;

    int a = 5;
    int b = 8;

    swap_(a, b);
    cout << a << " " << b << endl;

    // Template Type Specification!
    cout << max_<int>(3.14, 4.22) << endl;
    cout << max_<double>(3, 4) << endl;

    Box<int> c;
    Box<double> d;
    Box<string> e;

    Pair<int, string> student;
    student.first = 13;
    student.second = "John";

    return 0;
}