//
// Created by linyxus on 17-9-23.
//

#ifndef DEEPER_NET_OPERATORS_H
#define DEEPER_NET_OPERATORS_H

/**
 * Derivative Operators
 * Variant: single
 * Data type: double
 *
 * Usage example:
 * typedef op_mul<variant, variant> fx;
 * double f = fx::f(1.0); // calculate f(1)
 * double dy = fx::d(1.0); // derivative of fx at x=1.0
 */

#include <cmath>


namespace dnet
{
    namespace derivative
    {
        // define variant of function
        struct variant;

        // const value
        // MAKE_VALUE({double_value}, {name})
        // then: constant<{name}> will create a constant holder containing {double_value}
        template <typename T>
        struct constant;

        template <typename L, typename R>
        struct op_plus;


        template <typename L, typename R>
        struct op_minus;

        template <typename L, typename R>
        struct op_mul;

        // B(ase) ^ E(xp)
        template <typename B, typename E>
        struct op_power;

        // L / R
        template <typename L, typename R>
        struct op_div;

        // log(B(ase), R(eal))
        template <typename B, typename R>
        struct op_log;

        template <typename R>
        struct op_ln;

        // macro
        #define MAKE_VALUE(V, NAME) struct NAME { static double value() { return V; } };






        struct variant
        {
            static double f(double v)
            {
                return v;
            }

            static double d(double v)
            {
                return 1;
            }
        };

        template <typename T>
        struct constant
        {
            static double f(double v)
            {
                return T::value();
            }

            static double d(double v)
            {
                return 0.0;
            }
        };

        template <typename L, typename R>
        struct op_plus
        {
            static double f(double v)
            {
                return L::f(v) + R::f(v);
            }

            static double d(double v)
            {
                return L::d(v) + R::d(v);
            }
        };

        template <typename L, typename R>
        struct op_minus
        {
            static double f(double v)
            {
                return L::f(v) - R::f(v);
            }

            static double d(double v)
            {
                return L::d(v) - R::d(v);
            }
        };

        template <typename L, typename R>
        struct op_mul
        {
            static double f(double v)
            {
                return L::f(v) * R::f(v);
            }

            static double d(double v)
            {
                return L::f(v) * R::d(v) + L::d(v) * R::f(v);
            }
        };

        template <typename B, typename E>
        struct op_power
        {
            static double f(double v)
            {
                return std::pow(B::f(v), E::f(v));
            }

            static double d(double v)
            {
                return B::d(v) * E::f(v) * std::pow(B::f(v), E::f(v) - 1)
                        + E::d(v) * f(v) * std::log(B::f(v));
            }
        };

        template <typename L, typename R>
        struct op_div
        {
            MAKE_VALUE(-1.0f, dc)
            typedef op_mul<L, op_power<R, constant<dc>>> __base;

            static double f(double v)
            {
                return __base::f(v);
            }

            static double d(double v)
            {
                return __base::d(v);
            }
        };

        template <typename R>
        struct op_ln
        {
            static double f(double v)
            {
                return std::log(R::f(v));
            }

            static double d(double v)
            {
                return 1.0f / R::f(v) * R::d(v);
            }
        };

        template <typename B, typename R>
        struct op_log
        {
            typedef op_div<op_ln<R>, op_ln<B>> __base;

            static double f(double v)
            {
                return __base::f(v);
            }

            static double d(double v)
            {
                return __base::d(v);
            }
        };
    }
}


#endif //DEEPER_NET_OPERATORS_H
