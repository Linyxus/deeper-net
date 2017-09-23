//
// Created by linyxus on 17-9-17.
//

#ifndef DEEPER_NET_RELU_H
#define DEEPER_NET_RELU_H

#include "activation.h"
#include "../../misc/exception.h"
#include <algorithm>

namespace dnet
{
    namespace nn
    {
        class relu;

        class relu : public activation
        {
        public:
            static unsigned int cnt;
            explicit relu(const matrix::axes_type &input_shape = matrix::axes_type({0, 0}));

            virtual const matrix &forwardp(const matrix &input) override;
            virtual const matrix &backp(const matrix &y_grad) override;
        private:
            matrix _prev_x;
        };

        unsigned int relu::cnt = 0;
    }
}

#endif //DEEPER_NET_RELU_H
