//
// Created by linyxus on 17-9-23.
//

#include "../../gtest/include/gtest/gtest.h"
#include "../../include/derivative/operators.h"

namespace
{
    using namespace dnet::derivative;

    MAKE_VALUE(1.0f, C0)
    MAKE_VALUE(2.33f, C1)
    MAKE_VALUE(-5.0f, C2)
    MAKE_VALUE(-1.0f, C3)
    MAKE_VALUE(4.0f, E4)
    MAKE_VALUE(3.0f, E3)
    MAKE_VALUE(2.0f, E2)
    MAKE_VALUE(std::exp(1.0f), E)
    MAKE_VALUE(0.0f, C_ZERO)

    TEST(der_operators, linear)
    {
        // y = 2.33x - 5
        typedef op_plus<op_mul<constant<C1>, variant>, constant<C2>> func;
        EXPECT_FLOAT_EQ(func::d(1.0f), 2.33f);
        EXPECT_FLOAT_EQ(func::d(100.0f), 2.33f);
        EXPECT_FLOAT_EQ(func::f(233.0f), 233.0f * 2.33f - 5.0f);
    }

    TEST(der_operators, higher)
    {
        // y = x(x+1)-5
        // dy/dx = 2x + 1
        typedef op_plus<op_mul<variant, op_plus<variant, constant<C0>>>, constant<C2>> func;
        EXPECT_FLOAT_EQ(func::d(1.0f), 3.0f);
        EXPECT_FLOAT_EQ(func::d(100.0f), 201.0f);
        EXPECT_FLOAT_EQ(func::f(1.0f), -3.0f);
    }

    TEST(der_operators, div_0)
    {
        // y = x / (x+1) = 1 - 1/(x+1)
        // dy/dx = 1/(x+1)^2
        typedef op_div<variant, op_plus<variant, constant<C0>>> func;
        EXPECT_FLOAT_EQ(func::f(1.0f), 0.5f);
        EXPECT_FLOAT_EQ(func::f(7.0f), 0.875f);
        EXPECT_FLOAT_EQ(func::d(1.0f), 0.25f);
        EXPECT_FLOAT_EQ(func::d(0.0f), 1.0f);
    }

    TEST(der_operators, power_0)
    {
        // y = x^4 + x^3 + x^2
        // dy/dx = 4x^3 + 3x^2 + 2x
        typedef op_power<variant, constant<E4>> x4;
        typedef op_power<variant, constant<E3>> x3;
        typedef op_power<variant, constant<E2>> x2;
        typedef op_plus<x4, op_plus<x3, x2>> func;
        EXPECT_FLOAT_EQ(func::f(1.0f), 3.0f);
        EXPECT_FLOAT_EQ(func::f(2.0f), 28.0f);
        EXPECT_FLOAT_EQ(func::d(1.0f), 9.0f);
        EXPECT_FLOAT_EQ(func::d(2.0f), 48.0f);
    }

    TEST(der_operators, power_e)
    {
        // y = e^x
        // dy/dx = e^x
        typedef op_power<constant<E>, variant> func;
        EXPECT_FLOAT_EQ(func::f(1.0f), std::exp(1.0f));
        EXPECT_FLOAT_EQ(func::f(1.5f), std::exp(1.5f));
        EXPECT_FLOAT_EQ(func::d(1.5f), std::exp(1.5f));
        EXPECT_FLOAT_EQ(func::d(3.1415f), std::exp(3.1415f));
    }

    TEST(der_operators, power_2)
    {
        // y = 2^x
        // dy/dx = 2^x * ln2
        typedef op_power<constant<E2>, variant> func;
        EXPECT_FLOAT_EQ(func::f(1.0f), 2.0f);
        EXPECT_FLOAT_EQ(func::f(3.0f), 8.0f);
        EXPECT_FLOAT_EQ(func::d(3.0f), std::log(2.0f) * 8.0f);
        EXPECT_FLOAT_EQ(func::d(3.1415f), std::log(2.0f) * std::pow(2.0, 3.1415f));
    }

    TEST(der_operators, log_e)
    {
        // y = lnx
        // dy/dx = 1/x
        typedef op_ln<variant> f;
        typedef op_div<op_ln<variant>, op_ln<constant<E>>> g;
        ASSERT_FLOAT_EQ(f::f(1.0f), 0.0f);
        ASSERT_FLOAT_EQ(f::d(1.0f), 1.0f);
        ASSERT_FLOAT_EQ(f::d(10.0f), 0.1f);
        EXPECT_FLOAT_EQ(g::d(10.0f), 0.1f);
        for (double x = 0.1; x < 10.0; x += 0.1)
        {
            EXPECT_FLOAT_EQ(f::f(x), g::f(x));
            EXPECT_FLOAT_EQ(f::d(x), g::d(x));
        }
    }

    TEST(der_operators, sigmoid)
    {
        // y = 1 / (1 + e^-x)
        // y' = y(1-y)
        typedef op_minus<constant<C_ZERO>, variant> _x;
        typedef op_power<constant<E>, _x> e_x;
        typedef op_div<constant<C0>, op_plus<constant<C0>, e_x>> func;
        ASSERT_FLOAT_EQ(func::f(0.0f), 0.5f);
        for (double x = -5.0; x <= 5.0; x += 0.1)
        {
            double f = func::f(x);
            EXPECT_FLOAT_EQ(func::d(x), f*(1-f));
        }
    }
}

