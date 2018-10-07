#ifndef FMIBOOK_VECTOR_H
#define FMIBOOK_VECTOR_H


template <typename T>
class Vector {
public:
    Vector(unsigned capacity = 10)
    : data(nullptr)
    , capacity(capacity)
    , size(0) {
        data = new T[capacity];
    }

    ~Vector() {
        delete[] data;
    }

    void addBack(const T& element) {
        if(size >= capacity) {
            resize();
        }

        data[size++] = element;
    }

    void removeAt(unsigned idx) {
        if(idx >= size) {
            return;
        }

        data[idx] = data[--size];
    }

    T& operator[](int index) {
        return data[index];
    }

    unsigned getSize() const {
        return size;
    }

private:
    T* data;
    unsigned size;
    unsigned capacity;

    void resize() {
        T* newData = new T[capacity*2];

        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity *= 2;
    }
};


#endif //FMIBOOK_VECTOR_H
