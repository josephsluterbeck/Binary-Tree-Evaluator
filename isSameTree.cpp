#include <iostream>
#include <vector>
#include <algorithm>
#include "BinarySearchTree.h"

// Function to collect elements of the tree into a vector
template<typename T>
void collectElements(BinaryNode<T>* node, std::vector<T>& elements) {
    if (node == nullptr) return;
    collectElements(node->getLeftChildPtr(), elements);
    elements.push_back(node->getItem());
    collectElements(node->getRightChildPtr(), elements);
}

// Function to check if two trees are equivalent
template<typename T>
bool isSameTree(BinarySearchTree<T>* tree1, BinarySearchTree<T>* tree2) {
    std::vector<T> elements1;
    std::vector<T> elements2;

    collectElements(tree1->getRoot(), elements1);
    collectElements(tree2->getRoot(), elements2);

    std::sort(elements1.begin(), elements1.end());
    std::sort(elements2.begin(), elements2.end());

    return elements1 == elements2;
}