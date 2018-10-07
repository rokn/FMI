#ifndef IMAGEEDITOR_VECTOR_IMPL_H
#define IMAGEEDITOR_VECTOR_IMPL_H

#include "Vector.h"

template<typename Data>
bool Vector<Data>::isEmpty() const {
    return size == 0;
}

template<typename Data>
void Vector<Data>::pushBack(const Data &newElement) {
    if(size >= capacity) {
        resize();
    }

    data[size++] = newElement;
}

template<typename Data>
Data Vector<Data>::popBack() {
    if(size == 0) {
        throw EmptyVectorException();
    }

    return data[--size];
}

template<typename Data>
void Vector<Data>::resize() {
    Data* newData = new Data[size*2];

    for (unsigned i = 0; i < size; ++i) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    size *= 2;
}

template<typename Data>
Vector<Data>::Vector(unsigned int capacity)
        : capacity(capacity)
        , size(0)
        , data(nullptr) {
    data = new Data[capacity];
}

template<typename Data>
Vector<Data>::~Vector() {
    delete[] data;
}

template<typename Data>
void Vector<Data>::clear() {
    size = 0;
}

template<typename Data>
Data& Vector<Data>::operator[](int index) const {
    return data[index];
}

template<typename Data>
unsigned Vector<Data>::getSize() const {
    return size;
}

template <typename Data>
Vector<Data>::Vector(const Vector<Data> &other)
        : size(other.size)
        , capacity(other.capacity)
        , data(nullptr) {
    data = new Data[capacity];

    for (unsigned i = 0; i < size; ++i) {
        data[i] = other[i];
    }
}

template<typename Data>
Vector<Data> & Vector<Data>::operator=(const Vector<Data> &other) {
    if(this != &other) {
        Data* temp = new Data[other.capacity];

        for (unsigned i = 0; i < other.size; ++i) {
            temp[i] = other[i];
        }

        size = other.size;
        capacity = other.capacity;
        delete[] data;
        data = temp;
    }

    return *this;
}

#endif //IMAGEEDITOR_VECTOR_IMPL_H
