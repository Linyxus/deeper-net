//
// Created by linyxus on 17-9-17.
//

#include "../../../include/nn/operators/relu.h"

namespace dnet
{
    namespace nn
    {

        relu::relu(const tensor<double, 2>::axes_type &input_shape)
            : _prev_x(input_shape), activation(input_shape)
        {
            this->input_shape = input_shape;
            this->output_shape = input_shape;
            this->id = "ReLU_" + std::to_string(dnet::misc::rand_int(100000));
        }

        matrix relu::forwardp(const matrix &input)
        {
            if (input.shape() != this->input_shape) {
                throw misc::make_error("Operator", "ReLU: input shape dismatch (" + this->id + ")");
            }
            this->_prev_x = input;
            matrix ret(input.shape());
            for (index_type i = 0; i < input.row(); i++) {
                for (index_type j = 0; j < input.col(); j++) {
                    ret[{i, j}] = std::max(0.0, input[{i, j}]);
                }
            }
            return ret;
        }

        backp_grads_type relu::backp(const matrix &y_grad)
        {
            if (y_grad.shape() != this->output_shape) {
                throw misc::make_error("Operator", "ReLU: y_grad shape dismatch (" + this->id + ")");
            }
            matrix ret(y_grad.shape());
            for (index_type i = 0; i < ret.row(); i++) {
                for (index_type j = 0; j < ret.col(); j++) {
                    if (this->_prev_x[{i, j}] > 0)
                        ret[{i, j}] = y_grad[{i, j}];
                    else
                        ret[{i, j}] = 0;
                }
            }
            return {ret, params_type()};
        }

        params_type relu::params()
        {
            return params_type();
        }
    }
}