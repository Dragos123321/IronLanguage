#include "Production.h"

Production::Production(const std::string& source, const std::set<std::string>& destinations) :
    m_source{ source },
    m_destinations{ destinations }
{
}

std::string Production::get_string() const
{
    std::string res = m_source + " -> ";

    for (const auto& destination : m_destinations) {
        res += destination + " | ";
    }

    res.pop_back();
    res.pop_back();
    res.pop_back();

    return res;
}

const std::string& Production::source() const
{
    return m_source;
}

const std::set<std::string>& Production::destinations() const
{
    return m_destinations;
}

bool operator<(const Production& el, const Production& other)
{
    return el.get_string() < other.get_string();
}
