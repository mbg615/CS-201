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
//            children[i + 2] = children[i + 1];
//            children[i + 1] = children[i];
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

//    void deleteKey(K key) {
//        int i = 0;
//        while(i < numKeys && key > keys[i]) {
//            i++;
//        }
//
//        if(isLeaf()) {
//            int j = i;
//            while(j < numKeys) {
//                keys[j] = keys[j + 1];
//                values[j] = values[j + 1];
//            }
//            return;
//        }
//
//        // ToDo: Finish
//
//
//    }

//    int deleteKey(K key) {
//        // ToDO: Verify this is correct
//        int i = 0;
//        while(i < numKeys && key > keys[i]) {
//            i++;
//        }
//
//        if(keys[i] == key) {
//            if(values[i].length() > 1) {
//                values[i].delFront();
//                return 1;
//            }
//
//            for(int j = i; j < numKeys - 1; j++) {
//                keys[j] = keys[j + 1];
//                values[j] = values[j + 1];
//                children[j] = children[j + 1];
//                children[j + 1] = children[j + 2];
//            }
//            keys[numKeys - 1] = K();
//            values[numKeys - 1] = V();
//            children[numKeys] = nullptr;
//            numKeys--;
//
//            return 1;
//        }
//
//        return 0;
//    }

private:

};
