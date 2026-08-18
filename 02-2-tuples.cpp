#include <iostream>
#include <tuple>

using namespace std;

/*
    When we have clear meaningful structure we can use Struct or Class instead of tuples.

    But when we need a temporary grouping of values then better to use tuples.
    - use tuples when we need to return multiple values from a function
    - use when we need a temporary heterogenious values
    - we are using structured bindings

    Use Struct or Class if we need:
    - the values represent ameaningful concept like (Student, Point, Employee)
    - we want descriptive member names (student.age instead of std::get<1>student)
    - the type will be used throughout the code
*/

// without tuples
class Student {
public:
    string name;
    int age;
    double gpa;
};


tuple<string, int, double> student(
    "Rustam",
    19,
    23.4
);

// instead of writing all the type we can use "make_tuple"
auto student1 = make_tuple(
    "Rustam",
    19,
    3.98
);


// Use Case 1: returning multiple values for functions int devide -> (quotient, remainder)
std::tuple<int, int> divide(int a, int b) {
    return {a / b, a % b};
}

// Example 1:
std::tuple<double, double> getPosition();

// Example 2: returning request response
std::tuple<bool, std::string, int> response();  // status, message, errorCode



int main() {
    Student student{"name", 19, 23.4};

    // we use <index> insted of [index], because tuples uses templates parameter
    cout << std::get<0>(student1) << endl;
    cout << std::get<1>(student1) << endl;
    cout << std::get<2>(student1) << endl;

    // modifying values
    std::get<1>(student1) = 25;

    auto result = divide(5, 2);
    cout << std::get<0>(result) << " " << std::get<1>(result) << endl;

    // Structured Binding
    auto [quotient, remainder] = divide(7, 4);
    cout << quotient << " " << remainder << endl;

    // Tuple Size
    cout << std::tuple_size<decltype(result)>::value << endl;

    // Tuple element type
    std::tuple_element<1, decltype(result)>::type;

    // Tuples comparison (is lexicographical)
    auto a = std::make_tuple(1, 2);
    auto b = std::make_tuple(1, 3);

    cout << (a < b) << endl;

    // Nested tuples
    auto nested = make_tuple (
        "Rustam",
        std::make_tuple(90, 95, 98)
    );

    
    return 0;
}