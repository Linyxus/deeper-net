//
// Created by linyxus on 17-8-30.
//

#ifndef DEEPER_NET_TENSOR_H
#define DEEPER_NET_TENSOR_H

template <typename T>
class tensor
{
public:
    tensor(T value);
    T value() const;
private:
    T _value;
};

template <typename T>
tensor<T>::tensor(T value)
{
    this->_value = value;
}

template <typename T>
T tensor<T>::value() const
{
    return this->_value;
}

#endif //DEEPER_NET_TENSOR_H
