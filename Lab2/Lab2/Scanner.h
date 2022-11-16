#pragma once

#include <vector>
#include "Pif.h"
#include "SymbolTable.h"
#include "Fa.h"

class Scanner
{
public:
    Scanner(const std::string& path, const std::string& tokens_file);
    ~Scanner() = default;

    void create_intermediate_file();

    std::pair<bool, std::pair<int, std::string>> try_parse();
    std::string parse();

    const Pif& get_pif() const;
    const SymbolTable& get_symTable() const;

private:
    std::string m_path;
    Pif m_pif;
    SymbolTable m_symTable;
    std::vector<std::string> m_tokens;
    Fa m_fa_int;
    Fa m_fa_identifier;
};