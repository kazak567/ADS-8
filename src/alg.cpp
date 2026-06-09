// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree_ref, const char* file_path) {
    std::ifstream fs(file_path);
    if (!fs.is_open()) {
        std::cerr << "Error: could not open " << file_path << std::endl;
        return;
    }

    std::string buffer = "";
    char c;
    
    while (fs.get(c)) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            buffer += std::tolower(static_cast<unsigned char>(c));
        } else {
            if (!buffer.empty()) {
                tree_ref.insert(buffer);
                buffer.clear();
            }
        }
    }
    
    if (!buffer.empty()) {
        tree_ref.insert(buffer);
    }
    
    fs.close();
}

void printFreq(BST<std::string>& tree_ref) {
    auto elements = tree_ref.getNodesSortedByFrequency();
    
    std::ofstream ofs("result/freq.txt");
    if (!ofs.is_open()) {
        std::cerr << "Error: cannot write to result/freq.txt" << std::endl;
        return;
    }

    for (size_t i = 0; i < elements.size(); ++i) {
        std::cout << elements[i].first << ": " << elements[i].second << std::endl;
        ofs << elements[i].first << ": " << elements[i].second << std::endl;
    }
    
    ofs.close();
}
