//
// Created by linyxus on 17-9-15.
//

#include "../../include/data_types/tensor.h"
#include "../../gtest/include/gtest/gtest.h"

namespace
{
    using std::vector;
    TEST(VECTOR_DIM, DIM_0) {
        vector_dim<int, 0>::type v = 1;
        EXPECT_EQ(v, 1);
    }

    TEST(VECTOR_DIM, DIM_1) {
        vector_dim<int, 1>::type v = {1,2,3};
        EXPECT_EQ(v.size(), 3);
        EXPECT_EQ(v[1], 2);
    }

    TEST(VECTOR_DIM, DIM_2) {
        vector_dim<int, 2>::type v = {{1,2,3}};
        EXPECT_EQ(v.size(), 1);
    }

    TEST(VECTOR_FLATTEN, DIM_1) {
        vector_dim<int, 1>::type v = {1,2,3};
        vector<int> res = vec_flater<int, 1>::flatten(v);
        EXPECT_EQ(res.size(), 3);
        EXPECT_EQ(res[2], 3);
        EXPECT_EQ(res[1], 2);
    }

    TEST(VECTOR_FLATTEN, DIM_2) {
        vector_dim<int, 2>::type v = {{1,2,3}, {4,5}};
        vector<int> res = vec_flater<int, 2>::flatten(v);
        EXPECT_EQ(res.size(), 5);
        EXPECT_EQ(res[0], 1);
        EXPECT_EQ(res[1], 2);
        EXPECT_EQ(res[3], 4);
        EXPECT_EQ(res[4], 5);
    }

    TEST(VECTOR_FLATTEN, DIM_3) {
        vector_dim<int, 3>::type v = {
                {
                        {1,2,3},
                        {4,5}
                },
                {
                        {6,7,8},
                        {9}
                }
        };
        vector<int> res = vec_flater<int, 3>::flatten(v);
        EXPECT_EQ(res.size(), 9);
        EXPECT_EQ(res, vector<int>({1,2,3,4,5,6,7,8,9}));
    }
}

