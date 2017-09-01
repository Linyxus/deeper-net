#include <iostream>
#include <array>
#include <utility>

void show(const std::initializer_list<int> &ini)
{
    for (auto x : ini) {
        std::cout << x << std::endl;
    }
}

int main()
{
    std::cout << "Hello, World!" << std::endl;
    show({123,234});
    return 0;
}