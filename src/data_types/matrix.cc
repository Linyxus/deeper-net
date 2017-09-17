//
// Created by linyxus on 17-9-16.
//

#include "../../include/data_types/matrix.h"

namespace dnet
{
    namespace data_types
    {
        matrix::matrix(const axes_type &size) : tensor(size) {}

        matrix::matrix(double def, const axes_type &size) : tensor(def, size) {}

        matrix::matrix(const vector_dim<double, 2>::type &data, const axes_type &size) : tensor(data, size) {}

        matrix matrix::T() const
        {
            matrix ret = *this;
            ret.swap_axis(0, 1);
            return ret;
        }

        matrix matrix::dot(const matrix &right) const
        {
            if (this->col() != right.row()) {
                throw misc::make_error("Matrix",
                                       "Matrix size dismatch. (" + std::to_string(this->row()) + ", "
                                       + std::to_string(this->col()) + ") * ("
                                       + std::to_string(right.row()) + ", "
                                       + std::to_string(right.col()) + ").");
            }
            matrix ret(0.0, {this->row(), right.col()});
            index_type l = this->col(); // == right.row()
            for (index_type i = 0; i < ret.row(); i++) {
                for (index_type m = 0; m < l; m++) {
                    for (index_type j = 0; j < ret.col(); j++)
                        ret[{i, j}] += (*this)[{i, m}] * right[{m, j}];
                }
            }
            return ret;
        }

        index_type matrix::col() const
        {
            return this->shape()[1];
        }

        index_type matrix::row() const
        {
            return this->shape()[0];
        }
    }
}
