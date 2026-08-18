#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <type_traits>
using namespace std;

/*
    Variadic Templates
*/

template<typename... Ts> class Magic {};

// template class Magic can accept unrestricted amount of parameters of any kind
Magic<int, vector<int>, map<string, vector<int>>> darkMagic;

// Since any number of parameters means we can call it with zero template parameter
Magic<> emptyMagic;

// If we want at least one we can do:
template<typename Required, typename... Args> class MagicFoo{};


// Unrestricted parameters for functions
template<typename... Args> void print(const string& str, Args... args);

// we can use 'sizeof' to calculate the size of parameters
template<typename... Ts>
void magic(Ts... args) {
    cout << "params: " << sizeof...(args) << endl;
}


/*  Recursive Template Function  */
template<typename T0>
void printf1(T0 value) {
    cout << value << endl;
}

template<typename T, typename... Ts>
void printf1(T value, Ts ...args) {
    cout << value << endl;
    printf1(args...);
}


/* Variable parameter template expansion C++17 */
template<typename T0, typename... T>
void printf2(T0 t0, T... t) {
    cout << t0 << endl;
    if constexpr (sizeof...(t) > 0) printf2(t...);
}

// Initialize list expansion old C++11 version
template<typename T, typename... Ts>
auto printf3(T value, Ts... args) {
    cout << value << endl;

    (void) initializer_list<T> {
        ([&args] {
            cout << args << endl;
        }(), value)...
    };
}

/*  Fold Expression C++17  */
template<typename ... T>
auto sum(T... t) {
    return (t + ...);
}

/*  Non-Type tempalte paramameter deduction  */
template<typename T, int BufSize>  // it means T will be deduced at compile time through call buffer_t<float, int> but not the BufSize
class buffer_t {
public:
    T& alloc();
    void free(T& item);
private:
    T data[BufSize];
};

// auto keyword
/*
    C++ 20
    template<auto value> void foo() {
        cout << value << endl;
        return;
    }
*/


// SFINAE - Substitution Failure If Not An Error
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
void describe(T) {  // Create describe(T) only if T is an integral type.
    cout << "Integral" << endl;
}
// We can read it as "Enable this function if T is integral."

/*
    SFINAE - is a mechanism
    enable_if = common tool using that mechanism

    SFINAE doesn't make the compiler accept bad code—it makes the compiler silently discard that particular template candidate.

    C++ 20 has more clearer version:
*/
template<T> requires std::integral<T>
void describe_(T) {
    cout << "Integral" << endl;
}


// Does type T have .size() function?
template<typename T>
auto has_size(const T& c) -> decltype(c.size(), std::true_type{}) {  // If c.size() exists returns true_type.
    return std::true_type{};
}
// If c.size() doesn't exist → SFINAE removes this function from consideration.
// then we have a fallback:
std::false_type has_size(...) {   // ... means essentially "I can accept anything"
    return std::false_type{};
}

has_size(vector<int>{});   // true_typr
has_size(42);  // false_type
// Try expression → if valid, choose this overload → otherwise SFINAE removes it → fallback returns false.

// C++20 concepts make this much cleaner:
template<typename T> 
concept HaSize = reuqires(T x) {
    x.size();
}

int main() {

    // we can pass any number of parametrs to the function
    magic();    // 0
    magic(4);   // 1
    magic(2, "");   // 2
    magic(5, '_', true);    // 3
    cout << endl;

    printf1(1, 2, "123", 1.1);
    
    printf2(10);
    printf2(10, 12, "321", true);

    cout << endl;
    printf3(2, "231", 'A', 10);

    cout << endl;
    cout << sum(10, 20, 30, 40, 50) << endl << endl;

    buffer_t<int, 100>;  // 100 as template parameter
    foo<10>();


    describe(42);
    /*
        Here T = int.
        std::is_integral_v<int> → true
        enable_if_t<true> → valid (void)
        So the function exists → ✅
    */

    describe(3.14);
    /*
        Here T = double.
        std::is_integral_v<double> → false
        enable_if_t<false> → invalid
        Because this happens during template substitution, SFINAE says: "No problem, just remove this function from the candidates."
        There is no other describe() → compiler says no matching function → ❌
    */

    return 0;
}