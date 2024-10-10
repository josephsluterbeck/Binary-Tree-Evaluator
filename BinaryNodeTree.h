#ifndef BINARY_NODE_TREE_H
#define BINARY_NODE_TREE_H

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcept.h"

template <typename T>
class BinaryNodeTree : public BinaryTreeInterface<T> {
private:
    BinaryNode<T>* rootPtr;

protected:
    int getHeightHelper(BinaryNode<T>* subTreePtr) const;
    int getNumberOfNodesHelper(BinaryNode<T>* subTreePtr) const;
    void destroyTree(BinaryNode<T>* subTreePtr);
    BinaryNode<T>* balancedAdd(BinaryNode<T>* subTreePtr, BinaryNode<T>* newNodePtr);
    void preorder(void visit(T&), BinaryNode<T>* treePtr) const;
    void inorder(void visit(T&), BinaryNode<T>* treePtr) const;
    void postorder(void visit(T&), BinaryNode<T>* treePtr) const;

    // Protected accessor for rootPtr
    BinaryNode<T>* getRootPtr() const { return rootPtr; }
    void setRootPtr(BinaryNode<T>* newRootPtr) { rootPtr = newRootPtr; }

public:
    BinaryNodeTree();
    BinaryNodeTree(const T& rootItem);
    BinaryNodeTree(const T& rootItem, const BinaryNodeTree<T>* leftTreePtr, const BinaryNodeTree<T>* rightTreePtr);
    BinaryNodeTree(const BinaryNodeTree<T>& tree);
    virtual ~BinaryNodeTree();

    bool isEmpty() const;
    int getHeight() const;
    int getNumberOfNodes() const;
    T getRootData() const;
    bool add(const T& newData);
    bool remove(const T& data);
    void clear();
    bool contains(const T& data) const;

    void preorderTraverse(void visit(T&)) const;
    void inorderTraverse(void visit(T&)) const;
    void postorderTraverse(void visit(T&)) const;

protected:
    BinaryNode<T>* copyTree(const BinaryNode<T>* treePtr) const;
    BinaryNode<T>* findNode(BinaryNode<T>* treePtr, const T& target, bool& success) const;
};

template <typename T>
BinaryNodeTree<T>::BinaryNodeTree() : rootPtr(nullptr) {}

template <typename T>
BinaryNodeTree<T>::BinaryNodeTree(const T& rootItem) {
    rootPtr = new BinaryNode<T>(rootItem, nullptr, nullptr);
}

template <typename T>
BinaryNodeTree<T>::BinaryNodeTree(const T& rootItem, const BinaryNodeTree<T>* leftTreePtr, const BinaryNodeTree<T>* rightTreePtr) {
    rootPtr = new BinaryNode<T>(rootItem, copyTree(leftTreePtr->rootPtr), copyTree(rightTreePtr->rootPtr));
}

template <typename T>
BinaryNodeTree<T>::BinaryNodeTree(const BinaryNodeTree<T>& tree) {
    rootPtr = copyTree(tree.rootPtr);
}

template <typename T>
BinaryNodeTree<T>::~BinaryNodeTree() {
    destroyTree(rootPtr);
}

template <typename T>
bool BinaryNodeTree<T>::isEmpty() const {
    return rootPtr == nullptr;
}

template <typename T>
int BinaryNodeTree<T>::getHeight() const {
    return getHeightHelper(rootPtr);
}

template <typename T>
int BinaryNodeTree<T>::getNumberOfNodes() const {
    return getNumberOfNodesHelper(rootPtr);
}

template <typename T>
T BinaryNodeTree<T>::getRootData() const {
    if (isEmpty())
        throw PrecondViolatedExcept("getRootData() called with an empty tree.");
    return rootPtr->getItem();
}

template <typename T>
bool BinaryNodeTree<T>::add(const T& newData) {
    BinaryNode<T>* newNodePtr = new BinaryNode<T>(newData);
    rootPtr = balancedAdd(rootPtr, newNodePtr);
    return true;
}

template <typename T>
bool BinaryNodeTree<T>::remove(const T& data) {
    return false;
}

template <typename T>
void BinaryNodeTree<T>::clear() {
    destroyTree(rootPtr);
    rootPtr = nullptr;
}

template <typename T>
bool BinaryNodeTree<T>::contains(const T& data) const {
    bool success;
    findNode(rootPtr, data, success);
    return success;
}

template <typename T>
void BinaryNodeTree<T>::preorderTraverse(void visit(T&)) const {
    preorder(visit, rootPtr);
}

template <typename T>
void BinaryNodeTree<T>::inorderTraverse(void visit(T&)) const {
    inorder(visit, rootPtr);
}

template <typename T>
void BinaryNodeTree<T>::postorderTraverse(void visit(T&)) const {
    postorder(visit, rootPtr);
}

template <typename T>
int BinaryNodeTree<T>::getHeightHelper(BinaryNode<T>* subTreePtr) const {
    if (subTreePtr == nullptr)
        return 0;
    else
        return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()),
            getHeightHelper(subTreePtr->getRightChildPtr()));
}

template <typename T>
int BinaryNodeTree<T>::getNumberOfNodesHelper(BinaryNode<T>* subTreePtr) const {
    if (subTreePtr == nullptr)
        return 0;
    else
        return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) +
        getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
}

template <typename T>
void BinaryNodeTree<T>::destroyTree(BinaryNode<T>* subTreePtr) {
    if (subTreePtr != nullptr) {
        destroyTree(subTreePtr->getLeftChildPtr());
        destroyTree(subTreePtr->getRightChildPtr());
        delete subTreePtr;
    }
}

template <typename T>
BinaryNode<T>* BinaryNodeTree<T>::balancedAdd(BinaryNode<T>* subTreePtr, BinaryNode<T>* newNodePtr) {
    if (subTreePtr == nullptr)
        return newNodePtr;
    else {
        BinaryNode<T>* leftPtr = subTreePtr->getLeftChildPtr();
        BinaryNode<T>* rightPtr = subTreePtr->getRightChildPtr();

        if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
            subTreePtr->setRightChildPtr(balancedAdd(rightPtr, newNodePtr));
        else
            subTreePtr->setLeftChildPtr(balancedAdd(leftPtr, newNodePtr));

        return subTreePtr;
    }
}

template <typename T>
void BinaryNodeTree<T>::preorder(void visit(T&), BinaryNode<T>* treePtr) const {
    if (treePtr != nullptr) {
        T theItem = treePtr->getItem();
        visit(theItem);
        preorder(visit, treePtr->getLeftChildPtr());
        preorder(visit, treePtr->getRightChildPtr());
    }
}

template <typename T>
void BinaryNodeTree<T>::inorder(void visit(T&), BinaryNode<T>* treePtr) const {
    if (treePtr != nullptr) {
        inorder(visit, treePtr->getLeftChildPtr());
        T theItem = treePtr->getItem();
        visit(theItem);
        inorder(visit, treePtr->getRightChildPtr());
    }
}

template <typename T>
void BinaryNodeTree<T>::postorder(void visit(T&), BinaryNode<T>* treePtr) const {
    if (treePtr != nullptr) {
        postorder(visit, treePtr->getLeftChildPtr());
        postorder(visit, treePtr->getRightChildPtr());
        T theItem = treePtr->getItem();
        visit(theItem);
    }
}

template <typename T>
BinaryNode<T>* BinaryNodeTree<T>::copyTree(const BinaryNode<T>* treePtr) const {
    BinaryNode<T>* newTreePtr = nullptr;
    if (treePtr != nullptr) {
        newTreePtr = new BinaryNode<T>(treePtr->getItem(), nullptr, nullptr);
        newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
        newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
    }
    return newTreePtr;
}

template <typename T>
BinaryNode<T>* BinaryNodeTree<T>::findNode(BinaryNode<T>* treePtr, const T& target, bool& success) const {
    if (treePtr == nullptr)
        return nullptr;

    if (treePtr->getItem() == target) {
        success = true;
        return treePtr;
    }
    else {
        BinaryNode<T>* tempPtr = findNode(treePtr->getLeftChildPtr(), target, success);
        if (!success)
            tempPtr = findNode(treePtr->getRightChildPtr(), target, success);
        return tempPtr;
    }
}

#endif
