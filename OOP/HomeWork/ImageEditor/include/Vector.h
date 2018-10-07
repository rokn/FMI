#ifndef IMAGEEDITOR_VECTOR_H
#define IMAGEEDITOR_VECTOR_H

#include <exception>

class EmptyVectorException : public std::exception {

}; // TODO

template <typename Data>
class Vector {
public:
    explicit Vector(unsigned capacity = 10);
    Vector(const Vector<Data>& other);
    Vector<Data>& operator=(const Vector<Data>& other);
    ~Vector();

    bool isEmpty() const;
    void pushBack(const Data& newElement);
    Data popBack();

    void clear();
    Data& operator[](int index) const;
    unsigned getSize() const;

private:
    Data* data;
    unsigned size;
    unsigned capacity;

    void resize();
};


#include "Vector.impl.h"

#endif //IMAGEEDITOR_VECTOR_H
