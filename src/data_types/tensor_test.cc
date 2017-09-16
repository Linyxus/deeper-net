//
// Created by linyxus on 17-9-15.
//

#include "../../include/data_types/tensor.h"
#include "../../include/data_types/tools.h"
#include "../../gtest/include/gtest/gtest.h"

namespace
{
    using std::vector;
    using namespace dnet::data_types;
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

    TEST(TENSOR, TO_INDEX) {
        tensor<int, 3> ts({2,3,4});
        EXPECT_EQ(ts.to_index({0,0,2}), 12*0+4*0+1*2);
        EXPECT_EQ(ts.to_index({0,1,2}), 12*0+4*1+1*2);
        EXPECT_EQ(ts.to_index({1,2,3}), 12*1+4*2+1*3);
    }

    TEST(TENSOR, INDEXING) {
        tensor<int, 3> ts(0, {3,4,5});
        EXPECT_EQ((ts[{1,2,3}]), 0);
        EXPECT_EQ((ts[{2,3,4}]), 0);
        ts[{1,2,3}] = 1;
        ts[{2,3,4}] = 2;
        EXPECT_EQ((ts[{1,2,3}]), 1);
        EXPECT_EQ((ts[{2,3,4}]), 2);
    }

    TEST(TENSOR, INITIALIZING_1) {
        tensor<int, 1> ts({1,2,3,4,5}, {5});
        EXPECT_EQ((ts[{0}]), 1);
        EXPECT_EQ((ts[{1}]), 2);
        EXPECT_EQ((ts[{3}]), 4);
    }

    TEST(TENSOR, INITIALIZING_2) {
        tensor<int, 2> ts({
                                  {1,2,3},
                                  {4,5,6}
                          }, {2,3});
        EXPECT_EQ((ts[{0,0}]), 1);
        EXPECT_EQ((ts[{0,2}]), 3);
        EXPECT_EQ((ts[{1,1}]), 5);
    }

    TEST(TENSOR, SWAP_AXIS) {
        tensor<int, 3> ts({
                                  {
                                          {1,2,3,4},
                                          {5,6,7,8},
                                          {9,10,11,12}
                                  },
                                  {
                                          {1,2,3,4},
                                          {5,6,7,8},
                                          {9,10,11,12}
                                  }
                          }, {2,3,4});
        EXPECT_EQ((ts[{1,1,2}]), 7);
        ts.swap_axis(1, 2);
        EXPECT_EQ((ts[{1,2,1}]), 7);
        ts.swap_axis(0, 1);
        EXPECT_EQ((ts[{2,1,1}]), 7);
        EXPECT_EQ((ts[{3,0,1}]), 8);
    }
}

