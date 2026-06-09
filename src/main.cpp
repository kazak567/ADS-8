// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>&, const char*);
void printFreq(BST<std::string>&);

int main() {
    BST<std::string> my_tree;
    makeTree(my_tree, "war_peace.txt");
    
    std::cout << "Tree depth: " << my_tree.depth() << std::endl;
    std::cout << "Word 'war' is " << (my_tree.search("war") ? "" : "not ") << "found.\n\n";
    
    printFreq(my_tree);
    
    return 0;
}
