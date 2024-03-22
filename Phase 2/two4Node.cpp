//
// Created by Maddox Guthrie on 3/11/24.
// Phase 2: two4Node.cpp
//

#include "CircularDynamicArray.cpp"

template<typename K, typename V>
class two4Node {

public:
    int numKeys;
    K keys[3];
    CircularDynamicArray<V> values[3];
    two4Node<K, V> *children[4];

    two4Node() {
        numKeys = 0;
    }

    bool isLeaf() {
        for(auto & chileNode : children) {
            if(chileNode != nullptr) return false;
        }
        return true;
    }

    void insertKey(K key, V value) {

    }

    void insertKey(K key, CircularDynamicArray<V> values) {

    }

    void insertDuplicate(K key, V value) {

    }

private:


};
