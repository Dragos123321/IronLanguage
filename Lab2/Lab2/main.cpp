#include "SymbolTable.h"

#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    SymbolTable sym_table;

    std::vector<std::string> symbols = { "a", "car", "3", "20", "ident1", "a", "3", "30", "a", "ident2", "red_car", "car", "100"};

    for ( auto symbol : symbols ) {
        std::cout << std::left << std::setw(3) << sym_table.add(symbol) << symbol << "\n";
    }

    return 0;
}