#include <string>
#include <map>
#include <iostream>
using namespace std;

/*
    Using structured binding, implement the following function with just one line of function code:
*/

template <typename Key, typename Value, typename F>
void update(map<Key, Value>& m, F foo) {
    // TODO
    for (auto&& [key, value] : m)
        value = foo(key);
}

int main() {
    map<string, long long int> m {
        {"a", 1},
        {"b", 2},
        {"c", 3}
    };

    update(m, [](string key) {
        return hash<string>{}(key);
    });

    for (auto&& [key, value] : m)
        cout << key << ":" << value << endl;

    return 0;
}

/*
    Why not just auto& or auto?
     - auto (by value) would copy each pair<const Key, Value> on every iteration — wasteful, 
       and mutating value wouldn't affect the original map.
     - auto& (lvalue reference) would work fine for a map specifically, since iterating a map always yields lvalues. 
       But it wouldn't work generically for containers that yield temporaries (rvalues) from their iterators.
     - auto&& works for both cases: it binds to an lvalue as an lvalue reference, and to an rvalue as an rvalue reference, 
       without copying either way.
     - The mechanism (reference collapsing)
       In a template/auto deduction context, T&& doesn't mean "rvalue reference" 
        — the compiler deduces T differently depending on what's bound:

    Bind to an lvalue X → T deduced as X&, so T&& = X& && = X& (collapses to lvalue ref)
    Bind to an rvalue X → T deduced as X, so T&& = X&& (stays rvalue ref)
    This is called reference collapsing, and it's the same rule that powers std::forward.
*/

