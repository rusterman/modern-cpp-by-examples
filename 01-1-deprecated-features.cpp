#include <iostream>
#include <functional>
using namespace std;

int add(int x, int y) {
    return x + y;
}


int main() {

    char *str = "hello world";  // deprecated
    const char *text = "Hello World";

    cout << str << endl;
    cout << text << endl;

    [out = ref(cout << "Result: " << add(3, 4))]() {
        out.get() << "\n";
    }();

    return 0;
}