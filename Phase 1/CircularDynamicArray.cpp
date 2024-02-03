//
// Created by Maddox Guthrie on 1/31/24.
//
#include <random>

template<class T>
class CircularDynamicArray {
private:
    int cap;
    int size;
    int front;

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
        T* newArray = new T[cap / 4];

        for(int i = 0; i < size; i++) {
            newArray[i] = array[(front + i) % cap];
        }

        delete[] array;
        array = newArray;
        cap /= 4;
        front = 0;
    }

    int partition(T arr[], int low, int high) {
        int randomIndex = low + int(random()) % (high - low + 1);
        std::swap(arr[randomIndex], arr[high]);

        T pivot = arr[high];
        int i = low - 1;

        for(int j = low; j < high; ++j) {
            if(arr[j] <= pivot) {
                std::swap(arr[++i + 1], arr[high]);
            }
        }

        std::swap(arr[i + 1], arr[high]);
        return ++i;
    }

    void quickSortHelper(T arr[], int low, int high) {
        if(low < high) {
            int partitionIndex = partition(arr, low, high);

            quickSortHelper(arr, low, partitionIndex - 1);
            quickSortHelper(arr, partitionIndex + 1, high);
        }
    }

    T quickSelectHelper(T arr[], int low, int high, int k) {
        if(low <= high) {
            int partitionIndex = partition(arr, low, high);

            if(partitionIndex == k - 1) {
                return array[partitionIndex];
            } else if(partitionIndex < k) {
                return quickSelectHelper(arr, (partitionIndex + 1) % cap, high, k);
            } else {
                return quickSelectHelper(arr, low, (partitionIndex - 1 + cap) % cap, k);
            }
        }

        return T();
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
        if(i < 0 || i >= cap) {
            throw std::out_of_range("Index out of bounds: " + std::to_string(i) + "\n");
        } else {
            i = (front + i) % cap;
            return array[i];
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

    void addFront(T v) {
        if (size == cap) {
            grow();
        }

        front = (front - 1 + cap) % cap;
        array[front] = v;
        size++;
    }

    void delEnd() {
        if(size > 0) {
            size--;
        }

        if(size < cap / 4) {
            shrink();
        }
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

    int capacity() {
        return cap;
    }

    void clear() {
        delete[] array;
        array = new T[cap = 2];
        size = 0;
    }

    T QSelect(int k) {
        if(k >= 0 && k < size) {
            T* arr = new T[size];
            for(int i = 0; i < size ; i++) {
                arr[i] = array[(front + i) % cap];
            }
            T result = quickSelectHelper(arr, 0, size, k);
            delete[] arr;
            return result;
        }

        return T();
    }

    void Sort() {
        // We will be using QuickSort because some of the work has already been done
        quickSortHelper(array, front, (front + size - 1) % cap);
    }

    int linearSearch(T e) {
        for(int i = 0; i < size; i++) {
            if(array[(front + i) % cap] == e) {
                return i;
            }
        }

        return -1;
    }

    int binSearch(T e) {
        int r = (front + size) % cap;
        int l = front;

        while(l <= r) {
            int m = l + (r - l) / 2;

            if(array[m] == e) {
                return m;
            } else if(array[m] < e) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        return -1;
    }
};