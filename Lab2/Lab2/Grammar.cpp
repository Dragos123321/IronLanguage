#include "Grammar.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "Utils.h"

Production get_production_from_str(const std::string& input) {
    auto trim_input = trim(input);

    auto pos = input.find("->");

    auto source = input.substr(0, pos - 1);

    auto str_destinations = input.substr(pos + 3);

    std::istringstream dest_ss(str_destinations);
    std::string destination;
    std::set<std::string> destionations;

    while (std::getline(dest_ss, destination, '|')) {
        destionations.insert(destination);
    }

    return Production(source, destionations);
}

void Grammar::parse(const std::string& file_path)
{
    std::ifstream in(file_path);
    std::string line;

    while (std::getline(in, line)) {
        if (line.size() > 0 && line[0] == 'N') {
            while (std::getline(in, line)) {
                if (line.find("}") != std::string::npos) {
                    break;
                }

                line = trim(line);

                if (line[line.size() - 1] == ',') {
                    line.pop_back();
                }

                m_nonterminals.insert(line);
            }
        }

        if (line.size() > 0 && line[0] == 'T') {
            while (std::getline(in, line)) {
                if (line.find("}") != std::string::npos) {
                    break;
                }

                line = trim(line);

                if (line[line.size() - 1] == ',') {
                    line.pop_back();
                }

                m_terminals.insert(line);
            }
        }

        if (line.size() > 0 && line[0] == 'P') {
            while (std::getline(in, line)) {
                if (line.find("}") != std::string::npos) {
                    break;
                }

                line = trim(line);

                if (line[line.size() - 1] == ',') {
                    line.pop_back();
                }

                Production production = get_production_from_str(line);

                m_productions.insert(production);
            }
        }

        if (line.size() > 0 && line[0] == 's') {
            line = trim(line);

            auto pos = line.find('=');

            m_start_symbol = line.substr(pos + 1);

            m_start_symbol = trim(m_start_symbol);
        }
    }

    in.close();
}

const std::set<std::string>& Grammar::get_nonterminals() const
{
    return m_nonterminals;
}

const std::set<std::string>& Grammar::get_terminals() const
{
    return m_terminals;
}

const std::set<Production>& Grammar::get_productions() const
{
    return m_productions;
}

const std::string& Grammar::get_start_symbol() const
{
    return m_start_symbol;
}

bool Grammar::isCFG() const
{
    return m_isCFG;
}
