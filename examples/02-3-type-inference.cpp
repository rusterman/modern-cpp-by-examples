#include <iostream>
#include <initializer_list>

using namespace std;

class MagicFoo {
public:
    vector<int> vec;

    MagicFoo(initializer_list<int> list) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            vec.push_back(*it);
        }
    }
};

// Tail Type Inference (problem we do not know what kind of type the add function will return)
template<typename R, typename T, typename U>
R add(T x, U y) {
    return x + y;
}

// Wrong solution: because we do not know the declaration type of (x + y) before function execution
// decltype(x + y) add(T x, T u) { return x + y; }

// Solution-1: trailing return type
template<typename T, typename U>
auto add3(T x, U y) -> decltype(x + y) {
    return x + y;
}

// Solution-2:
template<typename T, typename U>
auto add4(T x, U y) {
    return x + y;
}


// decltype(auto)
bool lookup = true;
string lookup2 = "look";

bool lookup_return() {
    return lookup;
}

string lookup2_return() {
    return lookup2;
}

// OR
decltype(auto) lookup_return_func() {
    return lookup;
}
decltype(auto) lookup2_return_func() {
    return lookup2;
}


int main() {

    MagicFoo foo{5, 3, 2, 5, 6};

    for (auto it = foo.vec.begin(); it != foo.vec.end(); ++it) {
        cout << *it << " ";
    } cout << endl;


    // Some common usages
    auto i = 5;
    auto p = new auto(10);

    cout << p[0] << endl;


    // auto as function arguments
    auto add1 = [](auto x, auto y) -> int {
        return x + y;
    };

    cout << add1(3.4, 5) << endl;

    // Note: auto cannot be used to derive array types yet:
    // auto auto_arr[10] = {p};

    // Decleration type: decltype
    auto x = 1;
    auto y = 2;
    decltype(x + y) z;

    cout << is_same<decltype(x), int>::value << endl;
    cout << is_same<decltype(x), float>::value << endl;
    cout << is_same<decltype(x), decltype(z)>::value << endl;

    cout << add3(5, 3.4) << endl;
    cout << add4(true, 3.4) << endl;

    // check if type derivation is correct
    auto w = add3<int, double>(1, 2.0);
    cout << is_same<decltype(w), double>::value << endl;

    return 0;
}