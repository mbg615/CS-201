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
        treeSize = 0;
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
        std::cout << "Inserting " << key << " : " << value << std::endl;

        if(root == nullptr) {
            root = new two4Node<K, V>();
            root->insertKey(key, value);
            treeSize++;
            return;
        }

        if(root->numKeys == 3) {
            auto *newRoot = new two4Node<K, V>();
            splitNode(newRoot, root);
            root = newRoot;
            treeSize++;
        }

        insertHelper(root, key, value);

        std::cout << "end!\n";
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

    void insertHelper(two4Node<K,V> *currentNode, K key, V value) {
        if(currentNode->isLeaf()) {
            currentNode->insertKey(key, value);
            return;
        }

        int i = 0;
        while(i < currentNode->numKeys && key > currentNode->keys[i]) {
            i++;
        }
        if(currentNode->children[i]->numKeys == 3) {
            splitNode(currentNode, currentNode->children[i]);
            insertHelper(currentNode, key, value);
        }

        insertHelper(currentNode->children[i], key, value);
    }

    void splitNode(two4Node<K,V> *parentNode, two4Node<K,V> *childNode) {
        if(childNode->numKeys != 3) {
            return;
        }

        std::cout << "Splitting node (";
        std::cout << childNode->keys[0] << ", " << childNode->keys[1] << ", " << childNode->keys[2] << ")\n";

        for(int i = 0; i < childNode->values[1].length(); i++) {
            parentNode->insertKey(childNode->keys[1], childNode->values[1][i]);
        }

        std::cout << "New root start: " << parentNode->keys[0] << parentNode->keys[1] << "\n";

        auto *leftNode = new two4Node<K,V>();
        auto *rightNode = new two4Node<K,V>();

        leftNode->numKeys = 1;
        leftNode->keys[0] = childNode->keys[0];
        leftNode->values[0] = childNode->values[0];
        leftNode->children[0] = childNode->children[0];
        leftNode->children[1] = childNode->children[1];


        rightNode->numKeys = 1;
        rightNode->keys[0] = childNode->keys[2];
        rightNode->values[0] = childNode->values[2];
        rightNode->children[0] = childNode->children[2];
        rightNode->children[1] = childNode->children[3];

        int i = 0;
        while(i < parentNode->numKeys && childNode->keys[1] > parentNode->keys[i]) {
            i++;
        }

        for (int j = parentNode->numKeys; j > i; j--) {
            parentNode->children[j + 1] = parentNode->children[j];
        }

        parentNode->children[i] = leftNode;
        parentNode->children[i + 1] = rightNode;

        delete childNode;
    }
};
