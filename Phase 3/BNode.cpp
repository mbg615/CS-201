//
// Created by Maddox Guthrie on 4/8/24.
//

template<class K>
class BNode {
public:
    int heapType = 0;
    K key;
    BNode<K> *leftNode = nullptr;
    BNode<K> *rightNode = nullptr;
    BNode<K> *children = nullptr;


    BNode() = default;

    explicit BNode(K key) {
        leftNode = this;
        rightNode = this;
        this->key = key;
    }

    BNode(const BNode<K> &src) {

    }

    BNode& operator=(const BNode<K> &src) {
        if(this == &src) return *this; // Self assignment catch

    }

    ~BNode() = default;

private:


};
