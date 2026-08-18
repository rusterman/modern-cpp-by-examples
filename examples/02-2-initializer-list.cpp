#include <iostream>
#include <initializer_list>
#include <set>
#include <list>
#include <deque>

class Numbers {
public:
    std::vector<int> data;

    Numbers(const std::vector<int>& v) : data(v) {}
    Numbers(std::initializer_list<int> list) {   // it is like vector view read-only
        for (int x : list)
            data.push_back(x);
    }
};

void print(std::initializer_list<int> list) {
    for (int e : list)
        std::cout << e << " ";
    std::cout << std::endl;

    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    } std::cout << std::endl;
}

// try to modify -> error
void f(std::initializer_list<int> list) {
    // *list.begin() = 10;
}

// Multiple Constructors
class Example {
public:
    Example(int x) {
        std::cout << "int\n";
    }

    Example(std::initializer_list<int> list) {
        std::cout << "initializer_list\n";
    }
};

// returning initializer list cause dangling pointer
std::initializer_list<int> get() {
    return {1, 2, 3, 4};
}

// how is it implemented
template<typename T>
class initializer_list {
private:
    T* first;
    size_t count;
public:
    const T* begin() const;
    const T* end() const;
    size_t size() const;
};

int main() {

    std::vector<int> values = {1, 2, 3, 4};

    Numbers nums(values);
    //Numbers nums({10, 12, 15});
    //Numbers nums{5, 3,9, 7};
    //Numbers nums(std::vector<int>{1, 2, 3, 4});

    print({5, 10, 15});

    Example a(5);
    Example b{5};

    // mant STL containers have initializer list constructor
    std::vector<int> v{1, 2, 3}; // actually it uses initialize list in background
    std::set<int> s{1, 2, 3};
    std::list<int> l{1, 2, 3};
    std::deque<int> d{1, 2, 3};

    std::cout << *get().begin() << std::endl;  // dangling pointer

    return 0;
}