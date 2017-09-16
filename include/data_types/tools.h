//
// Created by linyxus on 17-8-31.
//

#ifndef DEEPER_NET_TOOLS_H
#define DEEPER_NET_TOOLS_H

#include "array.h"
#include "tensor.h"
#include <iostream>
#include <ctime>

// ***** Defination *****

template <typename T>
std::ostream & operator<<(std::ostream & out, const array<T> &arr);

template <typename T, unsigned int N>
std::ostream & operator<<(std::ostream & out, const dnet::data_types::tensor<T, N> &ts);

template <typename R>
void time_it(R r);

// ***** Implementation *****

template <typename T>
std::ostream & operator<<(std::ostream & out, const array<T> &arr)
{
    out << "[";
    for (int i = 0; i < arr.length(); i++) {
        out << " " << arr[i] << " ";
        if (i % 5 == 0)
            out << std::endl;
    }
    out << "]";
    return out;
}

template<typename T, unsigned int N>
std::ostream &operator<<(std::ostream &out, const dnet::data_types::tensor<T, N> &ts)
{

}

namespace dnet {
    namespace tools
    {
        template<typename R>
        void time_it(R r)
        {
            std::clock_t t1 = std::clock();
            r();
            double dur = (std::clock() - t1) / (double) CLOCKS_PER_SEC;
            std::cout << "Duration: " << dur << " s" << std::endl;
        }
    }
}

#endif //DEEPER_NET_TOOLS_H
