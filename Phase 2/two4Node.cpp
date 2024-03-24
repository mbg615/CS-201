//
// Created by Maddox Guthrie on 3/11/24.
// Phase 2: two4Node.cpp
//

#include "CircularDynamicArray.cpp"

template<typename K, typename V>
class two4Node {

public:
    int numKeys = 0;
    K keys[3];
    CircularDynamicArray<V> values[3];
    two4Node<K, V> *children[4];

    two4Node() {
        numKeys = 0;
        for(auto & child : children) {
            child = nullptr;
        }
        for(int i = 0; i < 3; i++) {
            keys[i] = K();
            values[i].clear();
        }
    }

    bool isLeaf() {
        for(auto & child : children) {
            if(child != nullptr) return false;
        }
        return true;
    }

    void insertKey(K key, V value) {
        int i = numKeys - 1;
        while(i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            values[i + 1] = values[i];
            children[i + 2] = children[i + 1];
            children[i + 1] = children[i];
            i--;
        }

        if(i >= 0 && keys[i] == key) {
            values[i].addEnd(value);
        } else {
            keys[i + 1] = key;
            values[i + 1].addEnd(value);
            numKeys++;
        }
    }

private:

};
