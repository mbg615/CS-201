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
//        if(root == nullptr) {
//            return 0;
//        }
//
//        removeHelper(root, key);
//        treeSize--;
    }

    int rank(K key) {
        return 0;
        // ToDo: Implement Later
    }

    K select(int pos) {
        return K();
        // ToDo: Implement Later
    }

    int duplicates(K key) {
        return duplicateHelper(root, key);
    }

    int size() {
        return treeSize;
    }

    void preorder() {
        preorderHelper(root);
    }

    void inorder(){
        inorderHelper(root);
        std::cout << std::endl;
    }

    void postorder() {
        postorderHelper(root);
    }

private:
    void destructorHelper(two4Node<K,V> *currentNode) {
        if(currentNode != nullptr) {
            destructorHelper(currentNode->children[0]);
            destructorHelper(currentNode->children[1]);
            destructorHelper(currentNode->children[2]);
            destructorHelper(currentNode->children[3]);
            delete currentNode;
        }
    }

    V *searchHelper(two4Node<K,V> *currentNode, K key) {
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

//    int removeHelper(two4Node<K,V> *currentNode, K key) {
//        if(currentNode == nullptr) return 0;
//
//        int i = 0;
//        while(i < currentNode->numKeys && key < currentNode->keys[i]) {
//            i++;
//        }
//
//        if(currentNode->keys[i] == key) {
//            if(currentNode->isLeaf()) {
//                currentNode->deleteKey(key);
//                return 1;
//            }
//
//            /* ToDo: Key found, find predecessor
//             *
//             */
//
//            return 1;
//        }
//
//        if(currentNode->children[i] == nullptr) return 0;
//
//        if(currentNode->children[i]->numKeys == 1) {
//            mergeHelper(currentNode, i);
//            /* ToDo: Figure out next steps
//            *
//            */
//        }
//
//        removeHelper(currentNode->children[i], key);
//    }

//    two4Node<K,V> *findPredecessor(two4Node<K,V> *currentNode, int keyIndex) {
//        // ToDo: Verify correctness
//        if(currentNode == nullptr) return nullptr;
//
//        if(currentNode->isLeaf()) return currentNode;
//
//        if(currentNode->children[keyIndex]->numKeys == 1) {
//            mergeHelper(currentNode, keyIndex);
//        }
//
//        findPredecessor(currentNode->children[keyIndex], currentNode->children[keyIndex]->numKeys);
//    }

//    void mergeHelper(two4Node<K,V> *parentNode, int nodeIndex) {
//        switch(nodeIndex) {
//            case 0:
//            case 1:
//            case 2:
//                // Merge right sibling.
//                if(parentNode->children[nodeIndex + 1]->numKeys == 1) {
//                    auto *mergedNode = new two4Node<K,V>();
//                    // Add keys
//                    mergedNode->numKeys = 3;
//                    mergedNode->keys[0] = parentNode->children[nodeIndex]->keys[0];
//                    mergedNode->keys[1] = parentNode->keys[nodeIndex];
//                    mergedNode->keys[2] = parentNode->children[nodeIndex + 1]->keys[0];
//                    // Add values
//                    mergedNode->values[0] = parentNode->children[nodeIndex]->values[0];
//                    mergedNode->values[1] = parentNode->values[nodeIndex];
//                    mergedNode->values[2] = parentNode->children[nodeIndex + 1]->values[0];
//                    // Link children
//                    mergedNode->children[0] = parentNode->children[nodeIndex]->children[0];
//                    mergedNode->children[1] = parentNode->children[nodeIndex]->children[1];
//                    mergedNode->children[2] = parentNode->children[nodeIndex+1]->children[0];
//                    mergedNode->children[3] = parentNode->children[nodeIndex+1]->children[1];
//                    // Delete old children
//                    delete parentNode->children[nodeIndex];
//                    delete parentNode->children[nodeIndex + 1];
//                    // Delete parent key
//                    parentNode->deleteKey(parentNode->keys[nodeIndex]);
//                    parentNode->children[nodeIndex + 1] = mergedNode;
//                    // Rotate from right sibling.
//                } else {
//                    // Add key to left child
//                    parentNode->children[nodeIndex]->insertKey(parentNode->keys[nodeIndex],parentNode->values[nodeIndex]);
//                    // Delete old key from parent
//                    parentNode->deleteKey(parentNode->keys[nodeIndex]);
//                    // Add new key to parent
//                    parentNode->insertKey(parentNode->children[nodeIndex + 1]->keys[0]);
//                    // Delete key from right child
//                    parentNode->children[nodeIndex + 1]->deleteKey(parentNode->children[nodeIndex + 1]->keys[0]);
//                    // Link leftmost right child's child to rightmost left child's child.
//                    parentNode->children[nodeIndex]->children[parentNode->children[nodeIndex]->numKeys] = parentNode->children[nodeIndex + 1]->children[0];
//                }
//                break;
//
//            case 3:
//                // Merge left sibling
//                if(parentNode->children[nodeIndex - 1]->numKeys == 1) {
//                    auto *mergedNode = new two4Node<K,V>();
//                    // Add Keys
//                    mergedNode->numKeys = 3;
//                    mergedNode->keys[0] = parentNode->children[nodeIndex - 1]->keys[0];
//                    mergedNode->keys[1] = parentNode->keys[nodeIndex - 1];
//                    mergedNode->keys[2] = parentNode->children[nodeIndex]->keys[0];
//                    // Add Values
//                    mergedNode->values[0] = parentNode->children[nodeIndex - 1]->values[0];
//                    mergedNode->values[1] = parentNode->values[nodeIndex - 1];
//                    mergedNode->values[2] = parentNode->children[nodeIndex]->values[0];
//                    // Link Children
//                    mergedNode->children[0] = parentNode->children[nodeIndex - 1]->children[0];
//                    mergedNode->children[1] = parentNode->children[nodeIndex - 1]->children[1];
//                    mergedNode->children[2] = parentNode->children[nodeIndex]->children[0];
//                    mergedNode->children[3] = parentNode->children[nodeIndex]->children[1];
//                    // Delete old children
//                    delete parentNode->children[nodeIndex - 1];
//                    delete parentNode->children[nodeIndex];
//                    // Delete parent key
//                    parentNode->deleteKey(parentNode->keys[nodeIndex - 1]);
//                    parentNode->children[nodeIndex] = mergedNode;
//                    // Rotate from left sibling
//                } else {
//                    // Add key to left child
//                    parentNode->children[nodeIndex]->insertKey(parentNode->keys[nodeIndex - 1]);
//                    // Delete old key from parent
//                    parentNode->deleteKey(parentNode->keys[nodeIndex - 1]);
//                    // Add new key to parent
//                    parentNode->insertKey(parentNode->children[nodeIndex - 1]->keys[parentNode->children[nodeIndex - 1]->numKeys]);
//                    // Delete key from right child
//                    parentNode->children[nodeIndex - 1]->deleteKey(parentNode->children[nodeIndex - 1]->keys[parentNode->children[nodeIndex - 1]->numKeys]);
//                    // Link leftmost right child's child to rightmost left child's child.
//                    parentNode->children[nodeIndex]->children[0] = parentNode->children[nodeIndex - 1]->children[parentNode->children[nodeIndex - 1]->numKeys];
//                }
//                break;
//
//            default:
//                std::cout << "Default Case Reached?" << std::endl;
//                return;
//        }
//    }

    void preorderHelper(two4Node<K,V> *currentNode) {
        if(currentNode != nullptr) {
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
    }

    void inorderHelper(two4Node<K,V> *currentNode) {
        if(currentNode != nullptr) {
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
    }

    void postorderHelper(two4Node<K,V> *currentNode) {
        if(currentNode != nullptr) {
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
    }

    int duplicateHelper(two4Node<K,V> *currentNode, K key) {
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
