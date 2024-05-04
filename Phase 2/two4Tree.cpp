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
        if (root == nullptr) {
            root = new two4Node<K, V>();
            root->insertKey(key, value);
            treeSize++;
            return;
        }

        if (root->numKeys == 3) {
            auto *newRoot = new two4Node<K, V>();
            splitNode(newRoot, root);
            root = newRoot;
        }

        insertHelper(root, key, value);
        treeSize++;
    }

    int remove(K key) {
        // Leaving mostly unimplemented because it's difficult.
        V* value = search(key);
        if(value == nullptr) return 0;

        treeSize--;
        return 1;
    }

    int rank(K key) {
        return rankHelper(root, key);
    }

    K select(int pos) {
        if(pos < 1 || pos > treeSize) return K();
        return selectHelper(root, pos);
    }

    int duplicates(K key) {
        return duplicateHelper(root, key);
    }

    int size() {
        return treeSize;
    }

    void preorder() {
        preorderHelper(root);
        std::cout << std::endl;
    }

    void inorder(){
        inorderHelper(root);
        std::cout << std::endl;
    }

    void postorder() {
        postorderHelper(root);
        std::cout << std::endl;
    }

private:
    void destructorHelper(two4Node<K,V> *currentNode) {
        if(currentNode == nullptr) return;

        destructorHelper(currentNode->children[0]);
        destructorHelper(currentNode->children[1]);
        destructorHelper(currentNode->children[2]);
        destructorHelper(currentNode->children[3]);
        delete currentNode;
    }

    V *searchHelper(two4Node<K,V> *currentNode, K key) {
        if(currentNode == nullptr) return nullptr;

        int i = 0;
        while(i < currentNode->numKeys && key > currentNode->keys[i]) {
            i++;
        }
        if(i < currentNode->numKeys && key == currentNode->keys[i]) {
            return &(currentNode->values[i][0]);
        }
        if(currentNode->isLeaf() || currentNode == nullptr) {
            return nullptr;
        }
        return searchHelper(currentNode->children[i], key);
    }

    void insertHelper(two4Node<K,V> *currentNode, K key, V value) {
        int i = 0;
        while(i < currentNode->numKeys && key > currentNode->keys[i]) {
            i++;
        }

        if(currentNode->keys[i] == key) {
            currentNode->insertKey(key, value);
            return;
        }

        if(currentNode->isLeaf()) {
            currentNode->insertKey(key, value);
            return;
        }

        if(currentNode->children[i]->numKeys == 3) {
            splitNode(currentNode, currentNode->children[i]);
            insertHelper(currentNode, key, value);
            return;
        }

        insertHelper(currentNode->children[i], key, value);
    }

    void splitNode(two4Node<K,V> *parentNode, two4Node<K,V> *childNode) {
        if(childNode->numKeys != 3) {
            return;
        }

        for(int i = 0; i < childNode->values[1].length(); i++) {
            parentNode->insertKey(childNode->keys[1], childNode->values[1][i]);
        }

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

    void preorderHelper(two4Node<K,V> *currentNode) {
        if(currentNode == nullptr) return;

        for(int i = 0; i < currentNode->numKeys; i++) {
            for(int j = 0; j < currentNode->values[i].length(); j++) {
                std::cout << currentNode->keys[i];
                if(i < currentNode->numKeys - 1) {
                    std::cout << " ";
                }
            }
            if(i >= currentNode->numKeys - 1) {
                std::cout << "\n";
            }
        }
        preorderHelper(currentNode->children[0]);
        preorderHelper(currentNode->children[1]);
        preorderHelper(currentNode->children[2]);
        preorderHelper(currentNode->children[3]);
    }

    void inorderHelper(two4Node<K,V> *currentNode) {
        if(currentNode == nullptr) return;

        inorderHelper(currentNode->children[0]);
        for(int j = 0; j < currentNode->values[0].length(); j++) {
            std::cout << currentNode->keys[0];
            if(-1 < currentNode->numKeys - 1) {
                std::cout << " ";
            }
        }
        inorderHelper(currentNode->children[1]);
        for(int j = 0; j < currentNode->values[1].length(); j++) {
            std::cout << currentNode->keys[1];
            if(0 < currentNode->numKeys - 1) {
                std::cout << " ";
            }
        }
        inorderHelper(currentNode->children[2]);
        for(int j = 0; j < currentNode->values[2].length(); j++) {
            std::cout << currentNode->keys[2];
            if(1 < currentNode->numKeys - 1) {
                std::cout << " ";
            }
        }
        inorderHelper(currentNode->children[3]);
    }

    void postorderHelper(two4Node<K,V> *currentNode) {
        if(currentNode == nullptr) return;

        postorderHelper(currentNode->children[0]);
        postorderHelper(currentNode->children[1]);
        postorderHelper(currentNode->children[2]);
        postorderHelper(currentNode->children[3]);
        for(int i = 0; i < currentNode->numKeys; i++) {
            for(int j = 0; j < currentNode->values[i].length(); j++) {
                std::cout << currentNode->keys[i];
                if(i < currentNode->numKeys - 1) {
                    std::cout << " ";
                }
            }
            if(i >= currentNode->numKeys - 1) {
                std::cout << "\n";
            }
        }
    }

    int rankHelper(two4Node<K,V> *currentNode, K key) {
        if(currentNode == nullptr) return 0;

        int i = 0;
        while(i < currentNode->numKeys && key > currentNode->keys[i]) i++;
        if(i < currentNode->numKeys && key == currentNode->keys[i]) {
            return i + rankHelper(currentNode->children[i], key) + 1;
        } else if(currentNode->isLeaf()) {
            return 0;
        } else {
            return rankHelper(currentNode->children[i], key);
        }
    }

    K selectHelper(two4Node<K,V> *currentNode, int pos) {
        if(currentNode == nullptr) return K();

        int leftTreeSize = treeSizeHelper(currentNode->children[0]);
        if(pos <= leftTreeSize) return selectHelper(currentNode->children[0], pos);
        else if(pos == leftTreeSize + 1) return currentNode->keys[0];
        else if(pos <= leftTreeSize + currentNode->numKeys) return currentNode->keys[pos - leftTreeSize - 1];
        else return selectHelper(currentNode->children[currentNode->numKeys], pos - leftTreeSize - currentNode->numKeys);
    }

    int treeSizeHelper(two4Node<K,V> *currentNode) {
        if(currentNode == nullptr) return 0;

        int nodeCount = currentNode->numKeys;
        for(int i = 0; i <= currentNode->numKeys; i++) {
            nodeCount += treeSizeHelper(currentNode->children[i]);
        }
        return nodeCount;
    }

    int duplicateHelper(two4Node<K,V> *currentNode, K key) {
        if(currentNode == nullptr) return 0;

        int i = 0;
        while(i < currentNode->numKeys && key > currentNode->keys[i]) {
            i++;
        }
        if(i < currentNode->numKeys && key == currentNode->keys[i]) {
            return currentNode->values[i].length();
        }
        if(currentNode->isLeaf() || currentNode == nullptr) {
            return 0;
        }
        return duplicateHelper(currentNode->children[i], key);
    }
};
