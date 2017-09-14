//
// Created by linyxus on 17-8-30.
//

#ifndef DEEPER_NET_TENSOR_H
#define DEEPER_NET_TENSOR_H

#include <utility>
#include <vector>
#include <array>

template <typename T, unsigned int N> class tensor;
template <typename T, unsigned int N> struct vector_dim;
template <typename T, unsigned int N> struct vec_flater;

template <typename T>
struct vector_dim<T, 0>
{
    typedef T type;
};

template <typename T, unsigned int N>
struct vector_dim
{
    typedef std::vector<typename vector_dim<T, N-1>::type> type;
};

template<typename T, unsigned int N>
std::vector<T> flatten_vec(typename vector_dim<T, N>::type);

template <typename T, unsigned int N>
class tensor
{
public:
    explicit tensor(typename vector_dim<T, N>::type data, std::array<int, N> size);
    tensor(std::array<int, N> size, const T& def);
    explicit tensor(std::array<int, N> size);
    int to_index(const std::array<int, N> &crd) const;
    void init(const std::array<int, N> &size);
private:
    std::vector<T> _data;
    std::array<int, N> _facts;
    std::array<int, N> _shape;
};

template <typename T, unsigned int N>
tensor<T, N>::tensor(typename vector_dim<T, N>::type data, std::array<int, N> size)
        : tensor(size)
{
    this->_data = vec_flater<T, N>::flatten(data);
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
void tensor<T, N>::init(const std::array<int, N> &sizes)
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

template <typename T>
struct vec_flater<T, 1>
{
    typedef std::vector<T> input_type;
    typedef std::vector<T> output_type;
    static output_type flatten(input_type arr) {
        return arr;
    }
};

template <typename T, unsigned int N>
struct vec_flater
{
    typedef typename vector_dim<T, N>::type input_type;
    typedef std::vector<T> output_type;
    static output_type flatten(input_type arr) {
        std::vector<T> ret;
        for (auto a : arr) {
            std::vector<T> res = vec_flater<T, N-1>::flatten(a);
            ret.insert(ret.end(), res.begin(), res.end());
        }
        return ret;
    }
};

#endif //DEEPER_NET_TENSOR_H
