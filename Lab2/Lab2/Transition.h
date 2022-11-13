#pragma once

#include <string>

class Transition
{
public:
    Transition(const std::string& source, const std::string& symbol, const std::string& destination);

    std::string get_string() const;

    friend bool operator< (const Transition& el, const Transition& other);

    const std::string& source() const;
    const std::string& symbol() const;
    const std::string& destination() const;

private:
    std::string m_source;
    std::string m_symbol;
    std::string m_destination;
};

