//
// Created by linyxus on 17-9-16.
//

#ifndef DEEPER_NET_MATRIX_H
#define DEEPER_NET_MATRIX_H

#include "tensor.h"
#include "../misc/exception.h"

namespace dnet
{
    namespace data_types
    {
        class matrix;

        class matrix : public tensor<double, 2>
        {
        public:
            explicit matrix(const axes_type &size);
            explicit matrix(const vector_dim<double, 2>::type &data, const axes_type &size);
            matrix(double def, const axes_type &size);

            matrix T() const;

            matrix dot(const matrix &right) const;

            index_type row() const;
            index_type col() const;
        };
    }
}

#endif //DEEPER_NET_MATRIX_H
