//
// Created by linyxus on 17-9-17.
//

#ifndef DEEPER_NET_OPERATOR_H
#define DEEPER_NET_OPERATOR_H

#include "../data_types/matrix.h"

namespace dnet
{
    namespace nn
    {
        using namespace data_types;
        class op;

        class op
        {
        public:
            virtual op();
            matrix::axes_type input_shape;
            matrix::axes_type output_shape;
            virtual const matrix &forwardp(const matrix &input) = 0;
            virtual const matrix &backp(const matrix &input) = 0;
            matrix params;
        };
    }
}

#endif //DEEPER_NET_OPERATOR_H
