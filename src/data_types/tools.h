//
// Created by linyxus on 17-8-31.
//

#ifndef DEEPER_NET_TOOLS_H
#define DEEPER_NET_TOOLS_H

#include "array.h"
#include <iostream>

// ***** Defination *****

template <typename T>
std::ostream & operator<<(std::ostream & out, const array<T> &arr);

// ***** Implementation *****

template <typename T>
std::ostream & operator<<(std::ostream & out, const array<T> &arr)
{
    out << "[";
    for (int i = 0; i < arr.length(); i++) {
        out << " " << arr[i] << " ";
    }
    out << "]";
    return out;
}

#endif //DEEPER_NET_TOOLS_H
