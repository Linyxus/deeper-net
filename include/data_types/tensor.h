//
// Created by linyxus on 17-8-30.
//

#ifndef DEEPER_NET_TENSOR_H
#define DEEPER_NET_TENSOR_H

#include <utility>
#include <vector>
#include <array>

template <typename T, unsigned int N> class tensor;
template <typename T, unsigned int N> struct initlist_dim;



template <typename T>
struct initlist_dim<T, 0>
{
    typedef T type;
};

template <typename T, unsigned int N>
struct initlist_dim
{
    typedef std::initializer_list<typename initlist_dim<T, N-1>::type> type;
};

template <typename T, unsigned int N>
std::vector<typename initlist_dim<T, N-1>::type> &&flatten_initlist(const typename initlist_dim<T, N>::type &ini);
template <typename T> std::vector<T> &&flatten_initlist<T, 1>(const std::initializer_list<T> &ini);

template <typename T, unsigned int N>
class tensor
{
public:
    explicit tensor(typename initlist_dim<T, N>::type data, std::array<int, N> size);
    tensor(std::array<int, N> size, const T& def);
    tensor(std::array<int, N> size);
    int to_index(const std::array<int, N> &crd) const;
    void init(const std::array<int, N> &size);
private:
    std::vector<T> _data;
    std::array<int, N> _facts;
    std::array<int, N> _shape;
};

template <typename T, unsigned int N>
tensor<T, N>::tensor(typename initlist_dim<T, N>::type data, std::array<int, N> size)
        : tensor(size)
{

}

template <typename T, unsigned int N>
tensor<T, N>::tensor(std::array<int, N> size, const T& def)
    : tensor(size)
{
    for (auto & x : this->_data) {
        x = def;
    }
}

template <typename T, unsigned int N>
tensor<T, N>::tensor(std::array<int, N> size)
{
    for (auto iter = size.begin(); iter != size.end(); iter++) {
        unsigned long i = iter - size.begin();
        if (i >= N) {
            break;
        }
        this->_shape[i] = *iter;
    }
    init(this->_shape);
}

template <typename T, unsigned int N>
void tensor::init(const std::array<int, N> &sizes)
{
    int fact = 1;
    for (int i = N-1; i >= 0; i--) {
        this->_facts[i] = fact;
        fact *= sizes[i];
    }
    this->_data.resize(fact);
}

template <typename T, unsigned int N>
int tensor<T, N>::to_index(const std::array<int, N> &crd) const
{
    int ret = 0;
    for (int i = 0; i < crd.size(); i++) {
        ret += crd[i] * this->_facts[i];
    }
    return ret;
}

#endif //DEEPER_NET_TENSOR_H
