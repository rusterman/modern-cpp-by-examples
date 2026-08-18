#include <iostream>
using namespace std;

int main() {
    system("clear");

    std::vector<int> vec = {1, 2, 3, 4};

    const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 2);
    if (itr != vec.end()) {
        *itr = 3;
    }

    const std::vector<int>::iterator itr2 = std::find(vec.begin(), vec.end(), 3);
    if (itr2 != vec.end()) {
        *itr2 = 4; 
    }

    for (std::vector<int>::iterator element = vec.begin(); element != vec.end(); ++element) {
        cout << *element << " ";
    } cout << endl;

    
    // C++17 eleminates
    // put temporarly varible to the if statement
    if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) {
        *itr = 4;
    }

    return 0;
}