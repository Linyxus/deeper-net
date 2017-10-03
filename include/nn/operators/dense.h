//
// Created by linyxus on 17-9-17.
//

#ifndef DEEPER_NET_DENSE_H
#define DEEPER_NET_DENSE_H

#include "operator.h"
#include "relu.h"

namespace dnet
{
    namespace nn
    {
        class dense;

        class dense : public op
        {
        public:
            dense(index_type output_dim, index_type input_dim = -1);
        };
    }
}

#endif //DEEPER_NET_DENSE_H
