//
// Created by linyxus on 17-10-3.
//

#include "../../../gtest/include/gtest/gtest.h"
#include "../../../include/nn/operators/operator.h"
#include "../../../include/misc/exception.h"

namespace {
    using dnet::nn::cal_dot_grad;
    using dnet::data_types::matrix;
    using dnet::misc::exception;

    class dot_grad_test : public ::testing::Test
    {
    protected:
        matrix *_W;
        matrix *_x;
        matrix *_grad_y;

        virtual void SetUp()
        {
            /**
             * Test info:
             * + 1 4 7 10 +T    + 1 +
             * | 2 5 8 11 |  *  | 2 |
             * + 3 6 9 12 +     + 3 +
             */
            _W = new matrix({
                                    {1, 4, 7, 10},
                                    {2, 5, 8, 11},
                                    {3, 6, 9, 12}
                            }, {3, 4});

            _x = new matrix({{1, 2, 3}}, {1, 3});
            *_x = _x->T();

            _grad_y = new matrix({{1, 2, 3, 4}}, {1, 4});
            *_grad_y = _grad_y->T();
        }

        virtual void TearDown()
        {
            delete _W;
            delete _x;
            delete _grad_y;
        }
    };

    TEST_F(dot_grad_test, error_input_not_vector)
    {
        try {
            cal_dot_grad(*_W, matrix({{1, 1}, {1, 1}}, {2, 2}), *_grad_y);
        }
        catch (const exception &e) {
            std::cout << e << std::endl;
        }
    }

    TEST_F(dot_grad_test, error_shape_mismatch)
    {
        try {
            cal_dot_grad(matrix({{1, 2}, {3, 4}}, {2, 2}), *_x, *_grad_y);
        }
        catch (const exception &e) {
            std::cout << e << std::endl;
        }
    }

    TEST_F(dot_grad_test, calculation)
    {
        auto res = cal_dot_grad(*_W, *_x, *_grad_y);
        auto grad_W = res.grad_w;
        auto grad_x = res.grad_x;
        EXPECT_EQ((grad_x[{0, 0}]), 70);
        EXPECT_EQ((grad_x[{1, 0}]), 80);
        EXPECT_EQ((grad_x[{2, 0}]), 90);
        EXPECT_EQ((grad_W[{0, 0}]), 1);
        EXPECT_EQ((grad_W[{0, 2}]), 3);
        EXPECT_EQ((grad_W[{1, 1}]), 4);
        EXPECT_EQ((grad_W[{2, 3}]), 12);
    }
}