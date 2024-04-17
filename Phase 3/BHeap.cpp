//
// Created by Maddox Guthrie on 4/8/24.
//

#include <cmath>
#include <vector>

#include "BNode.cpp"

template<class K>
class BHeap {
private:
    BNode<K> *minElement = nullptr; // Pointer to minimum element in heap
    int size = 0;

public:
    BHeap() {
        minElement = nullptr;
    }

    BHeap(K keys[], int s) {
        for(int i = 0; i < s; i++) { // Insert each key in heap
            insert(keys[i]);
        }

        consolidate();
    }

    BHeap(const BHeap<K> &src) {

    }

    BHeap& operator=(const BHeap<K> &src) {
        if(this == &src) return *this; // Self assignment catch

    }

    ~BHeap() {
        destructorHelper(minElement);
    }

    K peekKey() {
        if(minElement == nullptr) return K(); // Nullptr check
        return minElement->key;
    }

    K extractMin() {
        if(minElement == nullptr) return K(); // Nullptr check

        K minKey = minElement->key;

        if(minElement->leftNode == minElement) { // Only element check
            if(minElement->children == nullptr) { // No children check
                delete minElement;
                minElement = nullptr;
                size = 0;
            }

            minElement = minElement->children;
            return minKey;
        }

        if(minElement->children == nullptr) { // No children check
            minElement->leftNode->rightNode = minElement->rightNode;
            BNode<K> *possibleMin = nullptr; // Assign new minElement
            if(minElement->leftNode < minElement->rightNode) {
                possibleMin = minElement->leftNode;
            } else {
                possibleMin = minElement->rightNode;
            }
            minElement->rightNode->leftNode = minElement->leftNode;
            delete minElement;
            minElement = possibleMin;
        }

        size--;
        return minKey;
    }

    void insert(K key) {
        auto newNode = new BNode<K>(key);

        if(minElement == nullptr) { // Empty heap check
            minElement = newNode;
            size = 1;
            return;
        }

        newNode->leftNode = minElement->leftNode;
        newNode->rightNode = minElement;
        minElement->leftNode->rightNode = newNode;
        minElement->leftNode = newNode;

        if(key < minElement->key) { // Reassign minElement;
            minElement = newNode;
        }

        size++;
    }

    void merge(BHeap<K> &H2) {
        if(H2.minElement == nullptr) return; // No H2 check

        minElement->leftNode->rightNode = H2.minElement;
        H2.minElement->leftNode->rightNode = minElement;
        BNode<K> *H2End = H2.minElement->leftNode;
        H2.minElement->leftNode = minElement->leftNode;
        H2End->rightNode = minElement;
        H2.minElement = nullptr;
        H2.size = 0;

        consolidate();
    }

    void printKey() {
        if(minElement == nullptr) return;
        BNode<K> *currentNode = minElement;

        do {
            std::cout << "B" << currentNode->heapType << ":\n";
            printKeyHelper(currentNode);
            currentNode = currentNode->rightNode;
            std::cout << "\n";
        } while(currentNode != minElement);

        std::cout << "\n\n\n";
    }

private:
    void destructorHelper(BNode<K> *currentNode) {
        return;
        if(currentNode == nullptr) return;

        if(currentNode->children == nullptr) {
            BNode<K> *nextNode = currentNode->rightNode;
            delete currentNode;
            destructorHelper(nextNode);
            return;
        }

        destructorHelper(currentNode->children);
    }

    void consolidate() {
        std::cout << "Consolidate called" << std::endl;
        int maxTreeRank = log2(size);

        std::vector<BNode<K>*> BTrees(maxTreeRank);
        BNode<K> *workingNode = minElement;
        BNode<K> *nextNode = minElement->rightNode;

        do {
            std::cout << "Doing for Key: " << workingNode->key << " Heap type: " << workingNode->heapType << std::endl;

            while(BTrees[workingNode->heapType] != nullptr) {
                std::cout << "Ran here!\n";
                workingNode = mergeNodes(workingNode, BTrees[workingNode->heapType]);
                BTrees[workingNode->heapType - 1] = nullptr;
            }

            BTrees[workingNode->heapType] = workingNode;
            workingNode = nextNode;
            nextNode = nextNode->rightNode;

        } while(workingNode != minElement and workingNode != nullptr);

        int i, prev, end;

        for(i = 0; i < maxTreeRank; i++) {
            if(BTrees[i] != nullptr) break;
        }

        prev = i;

        for(end = maxTreeRank - 1; end >= i; end--) {
            if(BTrees[end] != nullptr) break;
        }

        BTrees[i]->leftNode = BTrees[end];
        BTrees[end]->rightNode = BTrees[i];

        for(i += 1; i < end; i++) {
            if(BTrees[i] != nullptr) {
                BTrees[i]->leftNode = BTrees[prev];
                BTrees[prev]->rightNode = BTrees[i];
                prev = i;
            }
        }

        minElement = nullptr;

        for(i = 0; i <= end; i++) {
            if(BTrees[i] != nullptr) {
                if(minElement == nullptr || BTrees[i]->key < minElement->key) {
                    minElement = BTrees[i];
                }
            }
        }
    }

//    BNode<K> *mergeNodes(BNode<K> *node1, BNode<K> *node2) {
//        if(node2->key < node1->key) {
//            if(node2->children == nullptr) {
//                node2->children = node1;
//                node2->heapType++;
//                return node2;
//            }
//
//            node2->children->leftNode->rightNode = node1;
//            node1->leftNode = node2->children->leftNode;
//            node2->children->leftNode = node1;
//            node1->rightNode = node2->children;
//            node2->heapType++;
//            return node2;
//        }
//        else {
//            if(node1->children == nullptr) {
//                node1->children = node2;
//                node1->heapType++;
//                return node1;
//            }
//
//            node1->children->leftNode->rightNode = node2;
//            node2->leftNode = node1->children->leftNode;
//            node1->children->leftNode = node2;
//            node2->rightNode = node1->children;
//            node1->heapType++;
//            return node1;
//        }
//    }

    BNode<K>* mergeNodes(BNode<K>* node1, BNode<K>* node2) {
        // Check if either node is NULL
        if (!node1) return node2;
        if (!node2) return node1;

        // Ensure node1 has smaller key
        if (node2->key < node1->key) {
            std::swap(node1, node2);
        }

        // Make node2 child of node1
        node2->rightNode = node1->children;
        if (node1->children) {
            node1->children->leftNode = node2;
        }
        node1->children = node2;

        // Update heap type and return node1
        node1->heapType++;
        return node1;
    }

    void printKeyHelper(BNode<K> *currentNode) {
        if(currentNode == nullptr) return; // Nullptr check
        std::cout << currentNode->key << " ";
        if(currentNode->children == nullptr) return; // No children check
        BNode<K> *originalChild = currentNode->children;
        currentNode = originalChild;
        do{
            printKeyHelper(currentNode);
            currentNode = currentNode->rightNode;
        } while(currentNode != nullptr && currentNode != originalChild);
    }
};
