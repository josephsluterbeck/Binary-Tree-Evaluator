#ifndef BINARY_NODE_H
#define BINARY_NODE_H

template <typename T>
class BinaryNode {
private:
    T item;
    BinaryNode<T>* leftChildPtr;
    BinaryNode<T>* rightChildPtr;

public:
    BinaryNode() : leftChildPtr(nullptr), rightChildPtr(nullptr) {}
    BinaryNode(const T& anItem) : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr) {}
    BinaryNode(const T& anItem, BinaryNode<T>* leftPtr, BinaryNode<T>* rightPtr)
        : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr) {}

    void setItem(const T& anItem) { item = anItem; }
    T getItem() const { return item; }

    bool isLeaf() const { return (leftChildPtr == nullptr && rightChildPtr == nullptr); }

    BinaryNode<T>* getLeftChildPtr() const { return leftChildPtr; }
    BinaryNode<T>* getRightChildPtr() const { return rightChildPtr; }

    void setLeftChildPtr(BinaryNode<T>* leftPtr) { leftChildPtr = leftPtr; }
    void setRightChildPtr(BinaryNode<T>* rightPtr) { rightChildPtr = rightPtr; }
};

#endif

