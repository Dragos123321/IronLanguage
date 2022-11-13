#pragma once

#include <set>
#include <string>
#include <vector>

#include "Transition.h"

class Fa
{
public:
    Fa() = default;
    ~Fa() = default;

    void parse(const std::string& file_path);

    const std::set<std::string>& get_states() const;
    const std::set<std::string>& get_alphabet() const;
    const std::set<Transition>& get_transitions() const;
    const std::string& get_initial_state() const;
    const std::set<std::string>& get_final_states() const;

    bool isDFA() const;

    bool check(const std::string& word);

private:
    std::set<std::string> m_states;
    std::set<std::string> m_alphabet;
    std::set<Transition> m_transitions;
    std::string m_initial_state;
    std::set<std::string> m_final_states;
    bool m_isDFA = true;
};

