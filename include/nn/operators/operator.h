//
// Created by linyxus on 17-9-17.
//

#ifndef DEEPER_NET_OPERATOR_H
#define DEEPER_NET_OPERATOR_H

#include "../../data_types/matrix.h"
#include "../../misc/exception.h"

namespace dnet
{
    namespace nn
    {
        using namespace data_types;

        typedef std::vector<double *> params_type;

        class op;

        struct dotgrad_ret_type;
        struct backp_grads_type;

        /**
         * calculate grad of W and x based on grad of their dot product y
         * >>> x and grad_y are vectors whose col equals ONE <<<
         * @param W matrix W is transposed, which means it has the same row as len(x) and the same column
         * as len(y)
         * @param x input vector during forward compute
         * @param grad_y grad of output vector y
         * @return contains two value: grad of W and grad of x
         */
        dotgrad_ret_type cal_dot_grad(const matrix &W, const matrix &x, const matrix &grad_y);

        struct dotgrad_ret_type
        {
            matrix grad_w;
            matrix grad_x;
        };

        struct backp_grads_type
        {
            matrix input;
            params_type params;
        };

        class op
        {
        public:
            op() {}

            matrix::axes_type input_shape;
            matrix::axes_type output_shape;

            /**
             * forwordprog period of node, calculate outputs and store the input for further calculation.
             * @param input input values
             * @return output values
             */
            virtual matrix forwardp(const matrix &input) = 0;

            /**
             * backprog period of node, calculate gradients of input and params.
             * @param y_grad the gradients of output
             * @return a structure consisting of gradients of input and parameters
             */
            virtual backp_grads_type backp(const matrix &y_grad) = 0;

            /**
             * return params of this node for optimization.
             * @return pointers of params for easy modification
             */
            virtual params_type params() = 0;

            // identity of this unit, for displaying structure
            std::string id;
        };
    }
}

#endif //DEEPER_NET_OPERATOR_H
