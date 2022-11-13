#include "Scanner.h"
#include "Fa.h"

#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    Fa fa;

    fa.parse("FA.in");

    auto states = fa.get_states();
    auto alphabet = fa.get_alphabet();
    auto transitions = fa.get_transitions();
    auto initial_state = fa.get_initial_state();
    auto final_states = fa.get_final_states();

    bool done = true;

    std::cout << "Menu:\n1 -> states\n2 -> alphabet\n3 -> transitions\n4 -> initial state\n5 -> final states\n0 -> exit\n\n";

    while (done) {
        int command;

        std::cout << "command>> ";
        std::cin >> command;

        switch (command) {
            case 0:
                done = false;
                break;
            case 1:
                std::cout << "States: \n";
                for (auto el : states) {
                    std::cout << el << '\n';
                }
                std::cout << '\n';
                break;
            case 2:
                std::cout << "Alphabet: \n";
                for (auto el : alphabet) {
                    std::cout << el << '\n';
                }
                std::cout << '\n';
                break;
            case 3:
                std::cout << "Transitions: \n";
                for (auto el : transitions) {
                    std::cout << el.get_string() << '\n';
                }
                std::cout << '\n';
                break;
            case 4:
                std::cout << "Initial state: \n" << initial_state << "\n\n";
                break;
            case 5:
                std::cout << "Final states: \n";
                for (auto el : final_states) {
                    std::cout << el << '\n';
                }
                std::cout << '\n';
                break;
            default:
                std::cout << "Invalid command\n\n";
        }
    }

    std::cout << std::boolalpha << fa.isDFA() << '\n';

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