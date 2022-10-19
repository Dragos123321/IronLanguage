#pragma once

#include <string>

struct Node {
    size_t index;
    std::string value;
    Node* left;
    Node* right;
};

class SymbolTable {
public:
    SymbolTable();

    size_t add(std::string symbol);

    std::pair<bool, size_t> find(std::string symbol);

    void remove(Node* node);

    ~SymbolTable();

private:
    Node* m_tree;
    size_t m_current_index;
};

