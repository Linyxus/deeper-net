//
// Created by linyxus on 17-9-17.
//

#ifndef DEEPER_NET_RELU_H
#define DEEPER_NET_RELU_H

#include "activation.h"
#include "../../misc/exception.h"
#include "../../misc/random.h"
#include <algorithm>

namespace dnet
{
    namespace nn
    {
        class relu;

        class relu : public activation
        {
        public:
            explicit relu(const matrix::axes_type &input_shape = matrix::axes_type({0, 0}));
            ~relu() {}

            virtual matrix forwardp(const matrix &input) override;
            virtual backp_grads_type backp(const matrix &y_grad) override;
            virtual params_type params() override;
        private:
            matrix _prev_x;
        };
    }
}

#endif //DEEPER_NET_RELU_H
