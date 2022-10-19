#include "SymbolTable.h"

SymbolTable::SymbolTable() : m_tree{ nullptr }, m_current_index{ 0 } {
}

size_t SymbolTable::add(std::string symbol) {
    if (m_tree == nullptr) {
        m_tree = new Node();
        m_tree->value = symbol;
        m_tree->index = m_current_index;
        m_tree->left = nullptr;
        m_tree->right = nullptr;

        m_current_index += 1;
        return m_tree->index;
    }

    auto pair_find = find(symbol);

    if (pair_find.first == true) {
        return pair_find.second;
    }

    Node* prev = nullptr;
    Node* current = m_tree;

    while (current != nullptr) {
        if (current->value < symbol) {
            prev = current;
            current = current->right;
        }
        else {
            prev = current;
            current = current->left;
        }
    }

    Node* new_node = new Node();
    new_node->index = m_current_index;
    new_node->value = symbol;
    new_node->left = nullptr;
    new_node->right = nullptr;

    if (prev->value < symbol) {
        prev->right = new_node;

        m_current_index += 1;

        return new_node->index;
    }
    else {
        prev->left = new_node;

        m_current_index += 1;

        return new_node->index;
    }
}

std::pair<bool, size_t> SymbolTable::find(std::string symbol) {
    if (m_tree == nullptr) {
        return std::make_pair(false, 0);
    }

    Node* current = m_tree;

    while (current != nullptr) {
        if (current->value == symbol) {
            return std::make_pair(true, current->index);
        }
        if (current->value < symbol) {
            current = current->right;
        }
        else {
            current = current->left;
        }
    }

    return std::make_pair(false, 0);
}

void SymbolTable::remove(Node* node) {
    if (node == nullptr)
        return;

    remove(node->left);
    remove(node->right);

    delete node;
    node = nullptr;
}

SymbolTable::~SymbolTable() {
    remove(m_tree);
}


