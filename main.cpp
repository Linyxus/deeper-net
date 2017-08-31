#include <iostream>
#include "src/data_types/tools.h"
#include "src/data_types/array.h"
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    array<int> a({1, 2, 3, 4, 5}, 3, 2);
    cout << a << endl;
    return 0;
}