//
// Created by linyxus on 17-8-30.
//

#ifndef DEEPER_NET_ARRAY_H
#define DEEPER_NET_ARRAY_H

#include <utility>
#include <exception>

// ***** Defination *****

template <typename T> class array;
template <typename T> class block_header;

template <typename T>
class array
{
public:
    array(std::initializer_list<T> init, int block_size=256, int depth=8);
    ~array();
    T & operator[](int i);
    const T &operator[](int i) const;
    void append(const T &);
    int length() const;
private:
    int _block_size;
    int _depth;
    int _length;
    block_header<T> *_tree;
};

template <typename T>
class block_header
{
    typedef block_header<T> *pblock_header;
public:
    explicit block_header(int block_size, bool leaf = false);
    block_header<T> *operator[](int i);
    const block_header<T> *operator[](int i) const;
    T *data();
    const T *data() const;
    void init_next(bool leaf);
    bool is_leaf() const;
private:
    block_header<T> **_tree;
    T *_data;
    int _next;
    int _block_size;
    bool _leaf;
};

// ***** Implementation *****

template <typename T>
array<T>::array(std::initializer_list<T> init, int block_size, int depth)
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
void array<T>::append(const T & value)
{

}

template <typename T>
block_header<T>::block_header(int block_size, bool leaf)
{
    this->_block_size = block_size;
    this->_leaf = leaf;
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

template <typename T>
block_header<T> *block_header<T>::operator[](int i)
{
    if (this->_leaf) {
        //throw exception here
    }
    if (i > this->_block_size) {
        //exp
    }
    return (this->_tree)[i];
}

template <typename T>
const block_header<T> *block_header<T>::operator[](int i) const
{
    if (this->_leaf) {
        //throw exception here
    }
    if (i > this->_block_size) {
        //exp
    }
    return (this->_tree)[i];
}

template <typename T>
T *block_header<T>::data()
{
    if (!this->_leaf) {
        //exp
    }
    return this->_data;
}

template <typename T>
const T *block_header<T>::data() const
{
    if (!this->_leaf) {
        //exp
    }
    return this->_data;
}

template <typename T>
void block_header<T>::init_next(bool leaf)
{
    if (this->_leaf) {
        //exp
    }
    if (this->_next >= this->_block_size) {
        //exp
    }
    this->_tree[this->_next++] = new block_header<T>(this->_block_size, leaf);
}

template <typename T>
bool block_header<T>::is_leaf() const
{
    return this->_leaf;
}

#endif //DEEPER_NET_ARRAY_H
