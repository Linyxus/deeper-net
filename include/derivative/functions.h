//
// Created by linyxus on 17-10-2.
//

#include "operators.h"
#include <cmath>

namespace dnet
{
    namespace derivative
    {
        namespace func
        {
            MAKE_VALUE(-1.0f, __1_C)
            MAKE_VALUE(1.0f, _1_C)
            MAKE_VALUE(0.0f, _0_C)
            MAKE_VALUE(std::exp(1.0), _E_C)

            // -x
            typedef op_minus<constant<_0_C>, variant> minus_x;
            // sigmoid: 1/(1+e^-x)
            typedef op_div <
                    constant<_1_C>,
                    op_plus <constant<_1_C>,
                            op_power <constant<_E_C>, minus_x>
                    >
                    >
                    Sigmoid;
            // x2
            typedef op_mul<variant, variant> x_2;

            // e^x
            typedef op_power<constant<_E_C>, variant> e_x;

            // e^-x
            typedef op_power<constant<_E_C>, minus_x> e__x;

            // tanh (e^x-e^-x)/(e^x+e^-x)
            typedef op_div <
                    op_minus<e_x, e__x>,
                    op_plus<e_x, e__x>,
                    >
                    tanh;

            // relu max{0. x}
            typedef op_max<constant<_0_C>, variant> ReLU;
        }
    }
}