#include <iostream>
#include <array>
#include "gtest/gtest.h"

void show(const std::initializer_list<int> &ini)
{
    for (auto x : ini) {
        std::cout << x << std::endl;
    }
}

namespace
{
    TEST(SHOW, SHOW_ARRAY) {
        show({1,2,3});
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}