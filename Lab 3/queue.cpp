//
// Created by Maddox Guthrie on 1/31/24.
//

template<class T>
class queue {
public:

    T* array;
    int size;
    int capacity;
    int front;

    queue() {
        array = new T[capacity = 10];
        size = front = 0;
    }

    queue(int s) {
        array = new T[capacity = s];
        size = front = 0;
    }

    ~queue() {
        delete[] array;
    }

    queue(const queue &old) {
        size = old.size;
        front = old.front;
        capacity = old.capacity;
        array = new T[capacity];
        for(int i = 0; i < capacity; i++) {
            array[i] = old.array[i];
        }
    }

    queue& operator=(const queue& rhs) {
        if(this == &rhs) {
            return *this;
        }

        delete[] array;

        size = rhs.size;
        capacity = rhs.size;
        front = rhs.front;
        array = new T[capacity];

        for(int i = 0; i < capacity; i++) {
            array[i] = rhs.array[i];
        }

        return *this;
    }

    void enqueue(T x) {
        array[(front + size++) % capacity] = x;
    }

    T dequeue() {
        int x = front;
        front = (front + 1) % capacity;
        size--;
        return array[x];
    }

};