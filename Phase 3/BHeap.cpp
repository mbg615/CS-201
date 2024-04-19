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
        std::cout << "Destructor called\n";
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
            } else {
                BNode<K> *newMin = minElement->children;
                delete minElement;
                minElement = newMin;
                size--;
                // ToDo: consolidate();
            }

            return minKey;
        }

        if(minElement->children == nullptr) { // No children check
            minElement->leftNode->rightNode = minElement->rightNode;
            minElement->rightNode->leftNode = minElement->leftNode;

            // Assign new minimum
            BNode<K> *currentNode = minElement->rightNode;
            BNode<K> *newMin = minElement->rightNode;
            do {
                if(currentNode->key < newMin->key) newMin = currentNode;
                currentNode = currentNode->rightNode;
            } while(currentNode != minElement->rightNode);

            delete minElement;
            minElement = newMin;
            size--;
            // ToDo: consolidate();
            return minKey;
        }

        minElement->leftNode->rightNode = minElement->children;
        minElement->rightNode->leftNode = minElement->children->leftNode;
        minElement->children->leftNode->rightNode = minElement->rightNode;
        minElement->children->leftNode = minElement->leftNode;

        BNode<K> *newMin = minElement->children;
        delete minElement;
        minElement = newMin;
        size--;
        // ToDo: consolidate();
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

        if(newNode->key < minElement->key) { // Reassign minElement;
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

        // ToDo: consolidate();
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
    }

private:
    void destructorHelper(BNode<K> *currentNode) {
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
        if(minElement == nullptr) return;

        int arraySize = log2(size) + 1;
        std::vector<BNode<K>*> treeArray(arraySize, nullptr);

        BNode<K> *workingNode = minElement;
        BNode<K> *nextNode = minElement->rightNode;

        do {
            while(treeArray[workingNode->heapType] != nullptr) {
                workingNode = mergeNodes(workingNode, treeArray[workingNode->heapType]);
                treeArray[workingNode->heapType - 1] = nullptr;
            }

            treeArray[workingNode->heapType] = workingNode;
            workingNode = nextNode;
            nextNode = nextNode->rightNode;
        } while(workingNode->key != minElement->key);

        int start = -1;
        int end;

        for(int i = 0; i < arraySize; i++) {
            if(treeArray[i] != nullptr && treeArray[i]->key < minElement->key) minElement = treeArray[i];
            if(start == -1 && treeArray[i] != nullptr) start = i;
            if(treeArray[i] != nullptr) end = i;
        }

        int prev = start;
        for(int i = start + 1; i <= end; i++) {
            if(treeArray[i] != nullptr) {
                treeArray[prev]->rightNode = treeArray[i];
                treeArray[i]->leftNode = treeArray[prev];
            }
        }

        treeArray[start]->leftNode = treeArray[end];
        treeArray[end]->rightNode = treeArray[start];
    }

    BNode<K>* mergeNodes(BNode<K>* node1, BNode<K>* node2) {
        // Check if either node is NULL
        if (!node1) return node2;
        if (!node2) return node1;

        // Ensure node1 has smaller key.
        if (node2->key < node1->key) {
            std::swap(node1, node2);
        }

        // If node one has no children, node2 becomes node1's child.
        if(node1->children == nullptr) {
            node1->children = node2;
            node2->leftNode = node2;
            node2->rightNode = node2;
        // link node2 into node1's child list.
        } else {
            node2->rightNode = node1->children;
            node2->leftNode = node1->children->leftNode;
            node1->children->leftNode->rightNode = node2;
            node1->children->leftNode = node2;
        }

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
