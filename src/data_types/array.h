//
// Created by linyxus on 17-8-30.
//

#ifndef DEEPER_NET_ARRAY_H
#define DEEPER_NET_ARRAY_H

#include <utility>
#include <exception>

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
    block_header(int block_size, bool leaf = false);
    block_header<T> *operator[](int i);
    const block_header<T> *operator[](int i) const;
    void set_data(T *);
    T *data();
template <typename T>
tensor::tensor(T value)
{
    this->_value = value;
}

template <typename T>
T tensor::value() const
{
    return this->_value;
}
    const T *data() const;
    void init_next() const;
    bool is_leaf() const;
private:
    block_header<T> **_tree;
    T *_data;
    int _next;
    int _block_size;
};

#endif //DEEPER_NET_ARRAY_H
