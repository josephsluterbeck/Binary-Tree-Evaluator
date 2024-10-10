#include <iostream>
#include <vector>
#include <algorithm>
#include "BinarySearchTree.h"
#include "isSameTree.cpp"

int main() {
    BinarySearchTree<std::string> tree1;
    BinarySearchTree<std::string> tree2;
    BinarySearchTree<std::string> tree3;

    tree1.add("abc");
    tree1.add("def");
    tree1.add("ghi");
    tree1.add("def");
    tree1.add("abc");
    tree1.add("ghi");

    tree2.add("abc");
    tree2.add("ghi");
    tree2.add("abc");
    tree2.add("def");
    tree2.add("ghi");

    tree3.add("abc");
    tree3.add("ghi");
    tree3.add("abc");
    tree3.add("def");
    tree3.add("ghi");

    // Test 1
    if (isSameTree(&tree1, &tree2)) {
        std::cout << "The trees are equivalent." << std::endl;
    }
    else {
        std::cout << "The trees are not equivalent." << std::endl;
    }

    // Test 2
    if (isSameTree(&tree3, &tree2)) {
        std::cout << "The trees are equivalent." << std::endl;
    }
    else {
        std::cout << "The trees are not equivalent." << std::endl;
    }

    return 0;
}
