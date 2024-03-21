//
// Created by Maddox Guthrie on 3/11/24.
// Phase 2: two4Tree.cpp
//

#include "two4Node.cpp"

template<typename K, typename V>
class two4Tree {

private:
    two4Node<K,V> *root;
    int treeSize; // Number of nodes in the tree

public:
    two4Tree() {
        root = nullptr;
        treeSize = 0;
    }

    two4Tree(K keys[], V values[], int size) {

    }

    ~two4Tree() {

    }

    V *search(K key) {

    }

    void insert(K key, V value) {

    }

    int remove(K key) {

    }

    int rank(K key) {

    }

    K select(int pos) {

    }

    int duplicates(K key) {

    }

    int size() {
        return treeSize;
    }

    void preorder() {

    }

    void inorder(){

    }

    void postorder() {

    }

private:

};
