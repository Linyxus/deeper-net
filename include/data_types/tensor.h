//
// Created by linyxus on 17-8-30.
//

#ifndef DEEPER_NET_TENSOR_H
#define DEEPER_NET_TENSOR_H

#include <utility>
#include <vector>
#include <array>

namespace dnet
{
    namespace data_types
    {
        typedef unsigned int index_type;

        template <typename T, unsigned int N>
        class tensor;

        template <typename T, unsigned int N>
        struct vector_dim;
        template <typename T, unsigned int N>
        struct vec_flater;

        template <typename T, unsigned int N>
        struct index_return;

        template <typename T>
        struct vector_dim<T, 0>
        {
            typedef T type;
        };

        template <typename T, unsigned int N>
        struct vector_dim
        {
            typedef std::vector<typename vector_dim<T, N - 1>::type> type;
        };

        template <typename T>
        struct index_return<T, 1>
        {
            typedef T type;
        };

        template <typename T, unsigned int N>
        struct index_return
        {
            typedef tensor<T, N-1> type;
        };

        template <typename T, unsigned int N>
        class tensor
        {
        public:
            typedef std::array<index_type, N> axes_type;

            explicit tensor(typename vector_dim<T, N>::type data, std::array<index_type, N> size);

            tensor(const T &def, std::array<index_type, N> size);

            explicit tensor(std::array<index_type, N> size);

            tensor(const tensor<T, N> &) = default;
            tensor(tensor<T, N> &&) noexcept = default;
            tensor<T, N> &operator=(const tensor<T, N> &) = default;
            tensor<T, N> &operator=(tensor<T, N> &&) noexcept = default;

            int to_index(const std::array<index_type, N> &crd) const;

            const T &operator[](const std::array<index_type, N> &i) const;
            T &operator[](const std::array<index_type, N> &i);

            const axes_type &facts() const;

            const axes_type &shape() const;

            void swap_axis(index_type i1, index_type i2);
        private:
            void init(const std::array<index_type, N> &sizes);

            std::vector<T> _data;
            axes_type _axes_sort;
            axes_type _facts;
            axes_type _shape;
        };

        template <typename T, unsigned int N>
        tensor<T, N>::tensor(typename vector_dim<T, N>::type data, std::array<index_type, N> size)
                : tensor(size)
        {
            this->_data = vec_flater<T, N>::flatten(data);
        }

        template <typename T, unsigned int N>
        tensor<T, N>::tensor(const T &def, std::array<index_type, N> size)
                : tensor(size)
        {
            for (auto &x : this->_data) {
                x = def;
            }
        }

        template <typename T, unsigned int N>
        tensor<T, N>::tensor(std::array<index_type, N> size)
        {
            for (auto iter = size.begin(); iter != size.end(); iter++) {
                unsigned long i = iter - size.begin();
                if (i >= N) {
                    break;
                }
                this->_shape[i] = *iter;
            }
            this->init(this->_shape);
        }

        template <typename T, unsigned int N>
        void tensor<T, N>::init(const std::array<index_type, N> &sizes)
        {
            for (index_type i = 0; i < this->_axes_sort.size(); i++) {
                _axes_sort[i] = i;
            }
            index_type fact = 1;
            for (int i = N - 1; i >= 0; i--) {
                this->_facts[i] = fact;
                fact *= sizes[i];
            }
            this->_data.resize(fact);
        }

        template <typename T, unsigned int N>
        int tensor<T, N>::to_index(const std::array<index_type, N> &crd) const
        {
            int ret = 0;
            for (int i = 0; i < crd.size(); i++) {
                ret += crd[i] * this->_facts[i];
            }
            return ret;
        }

        template <typename T, unsigned  int N>
        const T &tensor<T, N>::operator[](const std::array<index_type, N> &i) const
        {
            axes_type ii;
            for (size_t t = 0; t < i.size(); t++)
                ii[this->_axes_sort[t]] = i[t];
            return this->_data[this->to_index(ii)];
        }

        template <typename T, unsigned int N>
        T &tensor<T, N>::operator[](const std::array<index_type, N> &i)
        {
            axes_type ii;
            for (size_t t = 0; t < i.size(); t++)
                ii[this->_axes_sort[t]] = i[t];
            return this->_data[this->to_index(ii)];
        }

        template <typename T, unsigned int N>
        const typename tensor<T, N>::axes_type &tensor<T, N>::facts() const
        {
            return this->_facts;
        }

        template <typename T, unsigned int N>
        const typename tensor<T, N>::axes_type &tensor<T, N>::shape() const
        {
            return this->_shape;
        }

        template <typename T, unsigned int N>
        void tensor<T, N>::swap_axis(index_type i1, index_type i2)
        {
            index_type t = this->_axes_sort[i1];
            this->_axes_sort[i1] = this->_axes_sort[i2];
            this->_axes_sort[i2] = t;
        }

        template <typename T>
        struct vec_flater<T, 1>
        {
            typedef std::vector<T> input_type;
            typedef std::vector<T> output_type;

            static output_type flatten(input_type arr)
            {
                return arr;
            }
        };

        template <typename T, unsigned int N>
        struct vec_flater
        {
            typedef typename vector_dim<T, N>::type input_type;
            typedef std::vector<T> output_type;

            static output_type flatten(input_type arr)
            {
                std::vector<T> ret;
                for (auto a : arr) {
                    std::vector<T> res = vec_flater<T, N - 1>::flatten(a);
                    ret.insert(ret.end(), res.begin(), res.end());
                }
                return ret;
            }
        };
    }
}

#endif //DEEPER_NET_TENSOR_H
