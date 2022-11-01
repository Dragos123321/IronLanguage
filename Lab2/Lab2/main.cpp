#include "Scanner.h"

#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    Scanner scanner1("../p1.txt", "../token.in");

    std::cout << scanner1.parse() << '\n';

    Scanner scanner2("../p2.txt", "../token.in");

    std::cout << scanner2.parse() << '\n';

    Scanner scanner3("../p3.txt", "../token.in");

    std::cout << scanner3.parse() << '\n';

    Scanner scanner1err("../p1err.txt", "../token.in");

    std::cout << scanner1err.parse() << '\n';
}