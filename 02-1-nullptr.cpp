#include <iostream>
#include <type_traits>
using namespace std;

void foo(int) {
    cout << "int" << endl;
}

void foo(char*) {
    cout << "pointer" << endl;
}

int main() {

    system("clear");

    char *ch1 = NULL;
    char *ch2 = nullptr;

    cout << NULL << " " << (size_t)(nullptr) << endl;

    cout << std::is_same<decltype(NULL), decltype(0)>::value << endl;
    cout << std::is_same<decltype(NULL), decltype(nullptr)>::value << endl;
    

    return 0;
}