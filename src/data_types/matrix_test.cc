//
// Created by linyxus on 17-9-16.
//

#include "../../include/data_types/matrix.h"
#include "../../gtest/include/gtest/gtest.h"

namespace
{
    using namespace dnet::data_types;

    //matrix transpose test
    TEST(matrix, T)
    {
        matrix m1({{1,2},{3,4}}, {2,2});
        EXPECT_EQ((m1[{1,0}]), 3);
        matrix m2 = m1.T();
        EXPECT_EQ((m2[{1,0}]), 2);
        EXPECT_EQ((m2[{0,1}]), 3);
    }

    //matrix dot test
    TEST(matrix, dot_match_1)
    {
        matrix m1({{1, 2}, {3, 4}}, {2, 2});
        matrix m2({{1}, {2}}, {2, 1});
        matrix m3 = m1.dot(m2);
        EXPECT_EQ(5, (m3[{0, 0}]));
        EXPECT_EQ(11, (m3[{1, 0}]));
    }

    //matrix dot test, case: size not match
    TEST(matrix, dot_notmatch_1)
    {
        matrix m1({{1, 2}, {3, 4}}, {2, 2});
        matrix m2({{1, 2}}, {1, 2});
        try {
            matrix m3 = m1.dot(m2);
        }
        catch (const dnet::misc::exception &e) {
            std::cout << e;
        }
    }
}