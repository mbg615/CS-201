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
        treeSize = size;
        for(int i = 0; i < size; i++) {
            insert(keys[i], values[i]);
        }
    }

    ~two4Tree() {
        destructorHelper(root);
    }

    V *search(K key) {
        return searchHelper(root, key);
    }

    void insert(K key, V value) {
        insertHelper(root, key, value);
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
    void destructorHelper(two4Node<K,V> *node) {
        if(node != nullptr) {
            destructorHelper(node->children[0]);
            destructorHelper(node->children[1]);
            destructorHelper(node->children[2]);
            destructorHelper(node->children[3]);
            delete node;
        }
    }

    V *searchHelper(two4Node<K,V> *node, K key) {
        int i = 0;
        while(i < node->numKeys && key > node->keys[i]) {
            i++;
        }
        if(i < node->numKeys && key == node->keys[i]) {
            return &(node->values[i][0]);
        }
        if(node->isLeaf() || node == nullptr) {
            return nullptr;
        }
        return searchHelper(node->children[i], key);
    }

    void insertHelper(two4Node<K,V> *node, K key, V value) {
        int i = 0;
        while(i < node->numKeys && key > node->keys[i]) {
            i++;
        }
        if(node->children[i]->numKeys == 3) {
            split(node, node->children[i]);
        }
        if(i < node->numKeys && key == node->keys[i]) {
            node->insertDuplicate(key, value);
            return;
        }
        if(node->isLeaf()) {
            node->insertKey(key, value);
            return;
        }
        insertHelper(node->children[i], key, value);
    }

    void split(two4Node<K,V> *parentNode, two4Node<K,V> *childNode) {
        K middleKey = childNode->keys[1];
        CircularDynamicArray<V> middleValue = childNode->values[1];
        parentNode->insertKey(middleKey, middleValue);

        int i = 0;
        while (parentNode->keys[i] != middleKey) {
            i++;
        }

        auto *leftNode = new two4Node<K,V>;
        leftNode->insertKey(childNode->keys[0], childNode->values[0]);
        leftNode->children[0] = childNode->children[0];
        leftNode->children[1] = childNode->children[1];
        auto *rightNode = new two4Node<K,V>;
        rightNode->insertKey(childNode->keys[2], childNode->values[2]);
        rightNode->children[0] = childNode->children[2];
        rightNode->children[1] = childNode->children[3];

        parentNode->children[i] = leftNode;
        parentNode->children[i+1] = rightNode;
    }
};
