//
// Created by linyxus on 17-9-17.
//

#include "../../../include/nn/operators/operator.h"

namespace dnet
{
    namespace nn
    {
        const dotgrad_ret_type &cal_dot_grad(const matrix &W, const matrix &x, const matrix &grad_y)
        {
            if (x.col() != 1 || grad_y.col() != 1) {
                throw misc::make_error("Operator", "When calculating grad of matrix dot product, "
                        "input value is not vector.");
            }
            if (W.row() != x.row() || W.col() != grad_y.row()) {
                throw misc::make_error("Operator", "When calculating grad of matrix dot product, "
                        "the shape of W dismatch the shape of x and grad_y.\n"
                        "Note: W is a transposed matrix different to the matrix used in dotting.\n"
                        "(y = W.T * x)"
                );
            }
            matrix grad_x = W.dot(grad_y);
            matrix grad_w({W.row(), W.col()});
            for (index_type i = 0; i < grad_w.row(); i++) {
                for (index_type j = 0; j < grad_w.col(); j++) {
                    grad_w[{i, j}] = x[{i, 0}] * grad_y[{j, 0}];
                }
            }
            return {grad_w, grad_x};
        }
    }
}

