#include "Scanner.h"
#include "Grammar.h"

#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    Grammar grammar;

    grammar.parse("g2.txt");

    auto nonterminals = grammar.get_nonterminals();
    auto terminals = grammar.get_terminals();
    auto productions = grammar.get_productions();
    auto start_symbol = grammar.get_start_symbol();

    bool done = true;

    std::cout << "Menu:\n1 -> nontermials\n2 -> terminals\n3 -> productions\n4 -> start symbol\n5 -> check cfg\n0 -> exit\n\n";

    while (done) {
        int command;

        std::cout << "command> ";
        std::cin >> command;

        switch (command) {
            case 0:
                done = false;
                break;
            case 1:
                std::cout << "Nonterminals: \n";
                for (auto el : nonterminals) {
                    std::cout << el << '\n';
                }
                std::cout << '\n';
                break;
            case 2:
                std::cout << "Terminals: \n";
                for (auto el : terminals) {
                    std::cout << el << '\n';
                }
                std::cout << '\n';
                break;
            case 3:
                std::cout << "Productions: \n";
                for (auto el : productions) {
                    std::cout << el.get_string() << '\n';
                }
                std::cout << '\n';
                break;
            case 4:
                std::cout << "Start symbol: \n" << start_symbol << "\n\n";
                break;
            case 5:
                std::cout << "Is cfg: " << std::boolalpha << grammar.isCFG() << "\n\n";
                break;
            default:
                std::cout << "Invalid command\n\n";
        }
    }

    std::cout << "\n-------------------------------------------------------------\n\n";

    Scanner scanner1("../p1.txt", "../token.in");

    std::cout << scanner1.parse() << '\n';

    Scanner scanner2("../p2.txt", "../token.in");

    std::cout << scanner2.parse() << '\n';

    Scanner scanner3("../p3.txt", "../token.in");

    std::cout << scanner3.parse() << '\n';

    Scanner scanner1err("../p1err.txt", "../token.in");

    std::cout << scanner1err.parse() << '\n';
}