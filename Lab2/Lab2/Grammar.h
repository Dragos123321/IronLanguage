#pragma once

#include <set>
#include <string>
#include <vector>

#include "Production.h"

class Grammar
{
public:
    Grammar() = default;
    ~Grammar() = default;

    void parse(const std::string& file_path);

    const std::set<std::string>& get_nonterminals() const;
    const std::set<std::string>& get_terminals() const;
    const std::set<Production>& get_productions() const;
    const std::string& get_start_symbol() const;

    bool isCFG() const;

private:
    std::set<std::string> m_nonterminals;
    std::set<std::string> m_terminals;
    std::set<Production> m_productions;
    std::string m_start_symbol;
    bool m_isCFG = true;
};