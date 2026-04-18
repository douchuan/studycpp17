#include "composite_demo.h"

#include <iostream>

int main() {
    auto root = std::make_unique<DirectoryNode>("root");
    auto docs = std::make_unique<DirectoryNode>("docs");
    docs->add(std::make_unique<FileNode>("readme.txt"));
    docs->add(std::make_unique<FileNode>("notes.md"));
    root->add(std::make_unique<FileNode>("main.cpp"));
    root->add(std::move(docs));
    std::cout << root->display() << "\n";
    return 0;
}
