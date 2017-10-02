//
// Created by linyxus on 17-10-2.
//

#include "../../../gtest/include/gtest/gtest.h"
#include "../../../include/nn/operators/relu.h"

namespace
{
    using dnet::nn::op;
    using dnet::nn::relu;
    using dnet::data_types::matrix;

    class relu_test : public ::testing::Test
    {
    protected:
        op *_relu0;
        matrix *_test_data;
        matrix *_test_data2;
        virtual void SetUp()
        {
            this->_relu0 = new relu({2, 2});
            std::cout << "Generated testing relu unit, id: " << this->_relu0->id << std::endl;
            this->_test_data = new matrix({{-1, 0}, {3, -10}}, {2, 2});
            this->_test_data2 = new matrix({{1, 2}, {10, -10}}, {2, 2});
        }
        virtual void TearDown()
        {
            delete this->_test_data;
            delete this->_test_data2;
            delete this->_relu0;
        }
    };

    TEST_F(relu_test, forwardp)
    {
        auto f = _relu0->forwardp(*_test_data);
        EXPECT_FLOAT_EQ((f[{0, 0}]), 0);
        EXPECT_FLOAT_EQ((f[{1, 0}]), 3);
    }

    TEST_F(relu_test, backp)
    {
        _relu0->forwardp(*_test_data);
        auto b = _relu0->backp(*_test_data2);
        auto inp = b.input;
        EXPECT_FLOAT_EQ((inp[{0, 0}]), 0);
        EXPECT_FLOAT_EQ((inp[{0, 1}]), 0);
        EXPECT_FLOAT_EQ((inp[{1, 0}]), 10);
    }
}
