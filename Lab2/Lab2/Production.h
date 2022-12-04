#pragma once

#include <string>
#include <set>

class Production
{
public:
    Production(const std::string& source, const std::set<std::string>& destinations);

    std::string get_string() const;

    friend bool operator< (const Production& el, const Production& other);

    const std::string& source() const;
    const std::set<std::string>& destinations() const;

private:
    std::string m_source;
    std::set<std::string> m_destinations;
};

