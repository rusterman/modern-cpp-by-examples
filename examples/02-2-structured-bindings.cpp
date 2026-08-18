#include <iostream>
#include <tuple>
#include <map>

using namespace std;

/*
    Structured Binding helps us to unpack and object, pairs, tuples, structs to mainy variables.
*/

std::tuple<string, int, double> student {
    "Rustam",
    24,
    3.95
};

std::tuple<int, int> divide(int a, int b) {
    return {a / b, a % b};
}

// Returning many values
std::tuple<bool, std::string, int> login() {
    return {true, "Success", 200};
}

int main() {
    
    // before structured binding
    string name = std::get<0>(student);
    int age = std::get<1>(student);
    double gpa = std::get<2>(student);

    // with structured binding
    auto [name_, age_, gpa_] = student;


    // pairs
    std::pair<int, string> p{10, "John"};
    auto [age__, name__] = p;

    cout << p.first << ":" << p.second << endl;
    cout << age__ << ":" << name__ << endl;


    // functions
    auto [quotient, remainder] = divide(20, 7);


    // arrays
    int arr[] = {10, 20, 30};
    auto [a, b, c] = arr;


    // structs
    struct Point {
        int x;
        int y;
    };

    Point p{5, 8};
    auto [x, y] = p;


    // Copy vs Reference
    x = 3;  // does not chanfe p.x

    // using reference
    auto& [p1, p2] = p;

    p1 = 3;  // changes p.x to 3

    // Using Constant Reference (read onyl)
    const auto& [d, e, f] = arr;
    // d = 34;  // not allowed


    // Iterating Through Maps
    std::map<string, int> ages;

    for (const auto& item : ages) {
        cout << item.first << endl;
        cout << item.second << endl;
    }

    for (const auto& [key, value] : ages) {
        cout << key << endl;
        cout << value << endl;
    }


    // Returning many values
    auto [status, message, code] = login();


    // Nested example
    std::pair<int, std::tuple<int, int>> value{
        5, 
        {10, 20}
    };

    auto [val, inner] = value;
    auto [i, j] = inner;


    // Mistakes
    auto& [f, s] = std::pair{2, 3};
    const auto& [t, k] = std::pair{2, 3};

    // Maps
    map<string, int> scores {{"alice", 10}, {"bob", 5}};
    for (const auto& [name, score] : scores) {
        cout << name << ": " << score << endl;
    }

    return 0;
}