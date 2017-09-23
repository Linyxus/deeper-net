//
// Created by linyxus on 17-9-23.
//

#ifndef DEEPER_NET_ACTIVATION_H
#define DEEPER_NET_ACTIVATION_H

#include "operator.h"

namespace dnet
{
    namespace nn
    {
        class activation;

        class activation : public op
        {
        public:
            explicit activation(const matrix::axes_type &input_shape = matrix::axes_type({0, 0})) {}
            virtual const matrix &forwardp(const matrix &input) override = 0;
            virtual const matrix &backp(const matrix &y_grad) override = 0;
        };
    }
}

#endif //DEEPER_NET_ACTIVATION_H
