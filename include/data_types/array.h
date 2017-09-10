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

template <typename T> void free_node(block_header<T> *node);

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
    int *_fact;
    unsigned int _max_length;
};

template <typename T>
class block_header
{
public:
    typedef block_header<T> *pblock_header;
    explicit block_header(int block_size, bool leaf = false);
    block_header<T> *operator[](int i);
    const block_header<T> *operator[](int i) const;
    T *data();
    const T *data() const;
    void init_next(bool leaf);
    bool is_leaf() const;
    int block_size() const;
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

    //initialize facts
    this->_fact = new int [depth];
    for (int i = 1, fact = block_size; i <= depth; i++, fact *= block_size) {
        this->_fact[depth-i] = fact;
    }
    this->_max_length = this->_fact[0];

    //initialize tree root
    this->_tree = new block_header<T>(block_size, depth == 1);

    for (auto x : init) {
        this->append(x);
    }
}

template<typename T>
array<T>::~array()
{
    free_node(this->_tree);
}

template <typename T>
T & array<T>::operator[](int i)
{
    if (this->_length+1 > this->_max_length) {
        //exp here
    }
    int loc = i; // current location in a node
    block_header<T> *node = this->_tree; // current node
    for (int i = 0; i < this->_depth; i++) {
        if (i == this->_depth - 1) { // this is a leaf layer
            T *data = node->data();
            return data[loc];
        }
        int choice = loc / this->_fact[i+1];
        loc = loc % this->_fact[i+1]; // use fact[i+1]: we need to jump to the next layer so we choose due to the next
        block_header<T> *next = (*node)[choice];
        if (next == nullptr) {
            // this condition is impossile, however, if it happens, it means that the code have some terrible bugs
        }
        node = (*node)[choice];
    }
}

template <typename T>
const T & array<T>::operator[](int i) const
{
    if (this->_length+1 > this->_max_length) {
        //exp here
    }
    int loc = i; // current location in a node
    block_header<T> *node = this->_tree; // current node
    for (int i = 0; i < this->_depth; i++) {
        if (i == this->_depth - 1) { // this is a leaf layer
            T *data = node->data();
            return data[loc];
        }
        int choice = loc / this->_fact[i+1];
        loc = loc % this->_fact[i+1]; // use fact[i+1]: we need to jump to the next layer so we choose due to the next
        block_header<T> *next = (*node)[choice];
        if (next == nullptr) {
            // this condition is impossile, however, if it happens, it means that the code have some terrible bugs
        }
        node = (*node)[choice];
    }
}

template <typename T>
void array<T>::append(const T & value)
{
    if (this->_length+1 > this->_max_length) {
        //exp here
    }
    int loc = this->_length; // current location in a node
    block_header<T> *node = this->_tree; // current node
    for (int i = 0; i < this->_depth; i++) {
        if (i == this->_depth - 1) { // this is a leaf layer
            T *data = node->data();
            data[loc] = value;

            this->_length++;
            return;
        }
        int choice = loc / this->_fact[i+1];
        loc = loc % this->_fact[i+1]; // use fact[i+1]: we need to jump to the next layer so we choose due to the next
        block_header<T> *next = (*node)[choice];
        if (next == nullptr) {
            // whether the current layer is previous to a leaf layer ?
            node->init_next(i == this->_depth - 2);
        }
        node = (*node)[choice];
    }
}

template <typename T>
int array<T>::length() const
{
    return this->_length;
}

template <typename T>
block_header<T>::block_header(int block_size, bool leaf)
{
    this->_block_size = block_size;
    this->_leaf = leaf;
    if (!leaf) {
        // non-leaf node, allocate memory for child nodes
        this->_tree = new pblock_header [block_size];
        for (int i = 0; i < this->_block_size; i++) {
            this->_tree[i] = nullptr;
        }
        _next = 0;
    }
    else {
        // leaf node, allocate memory for data
        this->_data = new T [block_size];
    }
}

template <typename T>
block_header<T> *block_header<T>::operator[](int i)
{
    if (this->_leaf) {
        // [] operator is aimed to accessing child nodes
        // throw exception here
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

template <typename T>
int block_header<T>::block_size() const {
    return this->_block_size;
}

template <typename T>
void free_node(block_header<T> *node)
{
    if (node->is_leaf()) { // leaf node, free data
        delete [] node->data();
    }
    else { // non-leaf node, free all child nodes
        for (int i = 0; i < node->block_size(); i++) {
            block_header<T> *next = (*node)[i];
            if (next != nullptr)
                free_node((*node)[i]);
        }
    }
    delete node;
}

#endif //DEEPER_NET_ARRAY_H
