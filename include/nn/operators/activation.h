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
            virtual matrix forwardp(const matrix &input) override = 0;
            virtual backp_grads_type backp(const matrix &y_grad) override = 0;
            virtual params_type params() override = 0;
        };
    }
}

#endif //DEEPER_NET_ACTIVATION_H
