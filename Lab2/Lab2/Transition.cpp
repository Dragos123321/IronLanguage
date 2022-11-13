#include "Transition.h"

Transition::Transition(const std::string& source, const std::string& symbol, const std::string& destination) :
    m_source{ source },
    m_symbol{ symbol },
    m_destination{ destination }
{}

std::string Transition::get_string() const
{
    return "(" + m_source + ", " + m_symbol + ") -> " + m_destination;
}

const std::string& Transition::source() const
{
    return m_source;
}

const std::string& Transition::symbol() const
{
    return m_symbol;
}

const std::string& Transition::destination() const
{
    return m_destination;
}

bool operator<(const Transition& el, const Transition& other)
{
    return el.get_string() < other.get_string();
}
