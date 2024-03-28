//
// Created by Maddox Guthrie on 1/31/24.
// Phase 2: CircularDynamicArray.cpp
// This is a stripped down version of the class from Phase 1
//

#include <random>
#include <stdexcept>
#include <iostream>

template<class T>
class CircularDynamicArray {
private:
    int cap;
    int size;
    int front;

    T outOfBoundsValue = T();

    void grow() {
        T* newArray = new T[cap * 2];

        for(int i = 0; i < size; i++) {
            newArray[i] = array[(front + i) % cap];
        }

        delete[] array;
        array = newArray;
        cap *= 2;
        front = 0;
    }

    void shrink() {
        T* newArray = new T[cap / 2];

        for(int i = 0; i < size; i++) {
            newArray[i] = array[(front + i) % cap];
        }

        delete[] array;
        array = newArray;
        cap /= 2;
        front = 0;
    }

public:
    T* array;

    CircularDynamicArray() {
        array = new T[cap = 2];
        front = 0;
        size = 0;
    }

    explicit CircularDynamicArray(int s) {
        array = new T[cap = size = s];
        front = 0;
    }

    CircularDynamicArray(const CircularDynamicArray<T> &src) {
        cap = src.cap;
        size = src.size;
        front = src.front;
        array = new T[cap];
        for(int i = 0; i < cap; i++) {
            array[i] = src.array[i];
        }
    }

    CircularDynamicArray& operator=(const CircularDynamicArray &src) {
        if(this == &src) {
            return *this;
        }

        delete[] array;
        cap = src.cap;
        size = src.size;
        front = src.front;
        array = new T[cap];
        for(int i = 0; i < cap; i++) {
            array[i] = src.array[i];
        }

        return *this;
    }

    ~CircularDynamicArray() {
        delete[] array;
    }

    T& operator[](int i) {
        try {
            if (i < 0 || i >= cap) {
                throw std::out_of_range("Index out of bounds: " + std::to_string(i) + "\n");
            }

            i = (front + i) % cap;
            return array[i];
        }
        catch(const std::out_of_range& e) {
            std::cout << "Index out of bounds: " + std::to_string(i) + "\n";
            return outOfBoundsValue;
        }
    }

    void addEnd(T v) {
        if(size == cap) {
            grow();
        }

        int index = (front + size) % cap;
        array[index] = v;
        size++;
    }

    void delFront() {
        if(size > 0) {
            front = (front + 1) % cap;
            size--;
        }

        if(size < cap / 4) {
            shrink();
        }
    }

    int length() {
        return size;
    }

    void clear() {
        delete[] array;
        array = new T[cap = 2];
        size = front = 0;
    }
};