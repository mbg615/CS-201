//
// Created by Maddox Guthrie on 1/31/24.
//
#include <random>
#include <stdexcept>

template<class T>
class CircularDynamicArray {
private:
    int cap;
    int size;
    int front;

    T outOfBoundsValue = T{};

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

    int partition(T arr[], int low, int high) {
        int randomIndex = low + int(random()) % (high - low + 1);
        std::swap(arr[randomIndex], arr[high]);

        T pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (arr[j] <= pivot) {
                std::swap(arr[++i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);

        return i + 1;
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
                return quickSelectHelper(arr, partitionIndex + 1, high, k);
            } else {
                return quickSelectHelper(arr, low, partitionIndex - 1, k);
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
        size = front = 0;
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
        // I will be using QuickSort because some of the work has already been done
        // The partition function for QuickSelect can be reused.
        T* arr = new T[size];
        for(int i = 0; i < size ; i++) {
            arr[i] = array[(front + i) % cap];
        }

        quickSortHelper(arr, 0, size - 1);
        for(int i = 0; i < size ; i++) {
            array[i] = arr[i];
        }

        front = 0;
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
        int right = (front + size) % cap;
        int left = front;

        while(left <= right) {
            int mid = left + (right - left) / 2;

            if(array[mid] == e) {
                return mid;
            } else if(array[mid] < e) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    }
};