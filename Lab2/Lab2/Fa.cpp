#include "Fa.h"

#include <fstream>
#include <iostream>

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s) {
    return rtrim(ltrim(s));
}

Transition get_transition_from_str(const std::string& input) {
    auto trim_input = trim(input);

    auto pos = trim_input.find(",");

    auto init_state = trim_input.substr(1, pos - 1);

    auto closing_par_pos = trim_input.find(")");

    auto symbol = trim_input.substr(pos + 2, closing_par_pos - pos - 2);

    pos = trim_input.find("->");

    pos += 3;

    auto fin_state = trim_input.substr(pos);

    return Transition(init_state, symbol, fin_state);
}

void Fa::parse(const std::string& file_path)
{
    std::ifstream in(file_path);
    std::string line;

    while (std::getline(in, line)) {
        if (line.size() > 0 && line[0] == 'Q') {
            while (std::getline(in, line)) {
                if (line.find("}") != std::string::npos) {
                    break;
                }

                line = trim(line);

                if (line[line.size() - 1] == ',') {
                    line.pop_back();
                }

                m_states.insert(line);
            }
        }

        if (line.size() > 0 && line[0] == 'E') {
            while (std::getline(in, line)) {
                if (line.find("}") != std::string::npos) {
                    break;
                }

                line = trim(line);

                if (line[line.size() - 1] == ',') {
                    line.pop_back();
                }

                m_alphabet.insert(line);
            }
        }

        if (line.size() > 0 && line[0] == 'f') {
            while (std::getline(in, line)) {
                if (line.find("}") != std::string::npos) {
                    break;
                }

                line = trim(line);

                if (line[line.size() - 1] == ',') {
                    line.pop_back();
                }

                Transition transition = get_transition_from_str(line);

                for (const auto& el : m_transitions) {
                    if (el.source() == transition.source() &&
                        el.symbol() == transition.symbol() &&
                        el.destination() != transition.destination()) {
                        m_isDFA = false;
                    }
                }

                if (transition.source() == "eps") {
                    m_isDFA = false;
                }

                m_transitions.insert(transition);
            }
        }

        if (line.size() > 0 && line[0] == 'q' && line[1] == '0') {
            line = trim(line);

            auto pos = line.find('=');

            m_initial_state = line.substr(pos + 1);

            m_initial_state = trim(m_initial_state);
        }

        if (line.size() > 0 && line[0] == 'F') {
            while (std::getline(in, line)) {
                if (line.find("}") != std::string::npos) {
                    break;
                }

                line = trim(line);

                if (line[line.size() - 1] == ',') {
                    line.pop_back();
                }

                m_final_states.insert(line);
            }
        }
    }

    in.close();
}

const std::set<std::string>& Fa::get_states() const
{
    return m_states;
}

const std::set<std::string>& Fa::get_alphabet() const
{
    return m_alphabet;
}

const std::set<Transition>& Fa::get_transitions() const
{
    return m_transitions;
}

const std::string& Fa::get_initial_state() const
{
    return m_initial_state;
}

const std::set<std::string>& Fa::get_final_states() const
{
    return m_final_states;
}

bool Fa::isDFA() const
{
    return m_isDFA;
}

std::vector<Transition> get_transition_from_state(const std::set<Transition>& transitions, const std::string& state) {
    std::vector<Transition> res;

    for (const auto& transition : transitions) {
        if (transition.source() == state) {
            res.push_back(transition);
        }
    }

    return res;
}

bool Fa::check(const std::string& word)
{
    std::string current = m_initial_state;

    for (size_t i = 0; i < word.size(); ++i) {
        auto transitions = get_transition_from_state(m_transitions, current);

        bool found = false;
        for (const auto& transition : transitions) {
            if (transition.symbol() == std::string(1, word[i])) {
                current = transition.destination();
                found = true;
            }
        }

        if (!found) {
            return false;
        }
    }

    for (const auto& fin : m_final_states) {
        if (current == fin) {
            return true;
        }
    }

    return false;
}
