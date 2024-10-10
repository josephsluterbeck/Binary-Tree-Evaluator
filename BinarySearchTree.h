#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "BinaryNodeTree.h"

template <typename T>
class BinarySearchTree : public BinaryNodeTree<T> {
public:
    BinarySearchTree();
    BinarySearchTree(const T& rootItem);
    BinarySearchTree(const BinarySearchTree<T>& tree);

    bool add(const T& newData);
    bool remove(const T& data);
    bool contains(const T& data) const;
    BinaryNode<T>* getRoot() const;

protected:
    BinaryNode<T>* placeNode(BinaryNode<T>* subTreePtr, BinaryNode<T>* newNodePtr);
    BinaryNode<T>* removeValue(BinaryNode<T>* subTreePtr, const T target, bool& success);
    BinaryNode<T>* removeNode(BinaryNode<T>* nodePtr);
    BinaryNode<T>* removeLeftmostNode(BinaryNode<T>* subTreePtr, T& inorderSuccessor);
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree() : BinaryNodeTree<T>() {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const T& rootItem) : BinaryNodeTree<T>(rootItem) {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& tree) : BinaryNodeTree<T>(tree) {}

template <typename T>
bool BinarySearchTree<T>::add(const T& newData) {
    BinaryNode<T>* newNodePtr = new BinaryNode<T>(newData);
    this->setRootPtr(placeNode(this->getRootPtr(), newNodePtr));
    return true;
}

template <typename T>
bool BinarySearchTree<T>::remove(const T& data) {
    bool success = false;
    this->setRootPtr(removeValue(this->getRootPtr(), data, success));
    return success;
}

template <typename T>
bool BinarySearchTree<T>::contains(const T& data) const {
    bool success = false;
    this->findNode(this->getRootPtr(), data, success);
    return success;
}

template <typename T>
BinaryNode<T>* BinarySearchTree<T>::getRoot() const {
    return this->getRootPtr();
}

template <typename T>
BinaryNode<T>* BinarySearchTree<T>::placeNode(BinaryNode<T>* subTreePtr, BinaryNode<T>* newNodePtr) {
    if (subTreePtr == nullptr) {
        return newNodePtr;
    }
    else if (subTreePtr->getItem() > newNodePtr->getItem()) {
        subTreePtr->setLeftChildPtr(placeNode(subTreePtr->getLeftChildPtr(), newNodePtr));
    }
    else {
        subTreePtr->setRightChildPtr(placeNode(subTreePtr->getRightChildPtr(), newNodePtr));
    }
    return subTreePtr;
}

template <typename T>
BinaryNode<T>* BinarySearchTree<T>::removeValue(BinaryNode<T>* subTreePtr, const T target, bool& success) {
    if (subTreePtr == nullptr) {
        success = false;
        return nullptr;
    }

    if (subTreePtr->getItem() == target) {
        subTreePtr = removeNode(subTreePtr);
        success = true;
    }
    else if (subTreePtr->getItem() > target) {
        BinaryNode<T>* tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else {
        BinaryNode<T>* tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

template <typename T>
BinaryNode<T>* BinarySearchTree<T>::removeNode(BinaryNode<T>* nodePtr) {
    if (nodePtr->isLeaf()) {
        delete nodePtr;
        nodePtr = nullptr;
        return nodePtr;
    }
    else if (nodePtr->getLeftChildPtr() == nullptr) {
        BinaryNode<T>* nodeToConnectPtr = nodePtr->getRightChildPtr();
        delete nodePtr;
        nodePtr = nullptr;
        return nodeToConnectPtr;
    }
    else if (nodePtr->getRightChildPtr() == nullptr) {
        BinaryNode<T>* nodeToConnectPtr = nodePtr->getLeftChildPtr();
        delete nodePtr;
        nodePtr = nullptr;
        return nodeToConnectPtr;
    }
    else {
        T newNodeValue;
        nodePtr->setRightChildPtr(removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue));
        nodePtr->setItem(newNodeValue);
        return nodePtr;
    }
}

template <typename T>
BinaryNode<T>* BinarySearchTree<T>::removeLeftmostNode(BinaryNode<T>* subTreePtr, T& inorderSuccessor) {
    if (subTreePtr->getLeftChildPtr() == nullptr) {
        inorderSuccessor = subTreePtr->getItem();
        return removeNode(subTreePtr);
    }
    else {
        subTreePtr->setLeftChildPtr(removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor));
        return subTreePtr;
    }
}

#endif

