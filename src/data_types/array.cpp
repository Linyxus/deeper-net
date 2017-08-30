//
// Created by linyxus on 17-8-30.
//

#include "array.h"

template <typename T>
array::array(std::initializer_list<T> init, int block_size, int depth)
{
    if (block_size < 1) {
        //throw exception here
    }
    if (depth < 1) {
        //throw exception here
    }
    this->_block_size = block_size;
    this->_depth = depth;
    for (auto x : init) {
        this->append(x);
    }
}

template <typename T>
block_header::block_header(int block_size, bool leaf)
{
    this->_block_size = block_size;
    if (!leaf) {
        this->_tree = new pblock_header [block_size];
        for (int i = 0; i < this->_block_size; i++) {
            this->_tree[i] = nullptr;
        }
        _next = 0;
    }
    else {
        this->_data = new T [block_size];
    }
}
