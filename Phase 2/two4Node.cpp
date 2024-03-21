//
// Created by Maddox Guthrie on 3/11/24.
// Phase 2: two4Node.cpp
//

#include "CircularDynamicArray.cpp"

template<typename K, typename V>
class two4Node {

public:
    int numKeys;
    K *keys;
    CircularDynamicArray<V> values;
    two4Node<K, V> *children;

    two4Node() {
        numKeys = 0;
        keys = new K[3]();
        values.clear();
        children = new two4Node<K,V>[4]();
    }

    ~two4Node() {
        delete[] keys;
        delete values;
        delete[] children;
    }

private:


};
