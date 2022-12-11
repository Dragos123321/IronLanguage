#pragma once

#include <string>
#include <vector>

#include "Production.h"

class Grammar
{
public:
    Grammar() = default;
    ~Grammar() = default;

    void parse(const std::string& file_path);

    const std::vector<std::string>& get_nonterminals() const;
    const std::vector<std::string>& get_terminals() const;
    const std::vector<Production>& get_productions() const;
    const std::string& get_start_symbol() const;

    bool isCFG() const;

private:
    std::vector<std::string> m_nonterminals;
    std::vector<std::string> m_terminals;
    std::vector<Production> m_productions;
    std::string m_start_symbol;
    bool m_isCFG = true;
};